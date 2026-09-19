#include "Dictionary.h"
#include "DictionaryManager.h"
#include "Exceptions.h"
#include <iostream>
#include <memory>
#include <string>

namespace {
void printMenu() {
    std::cout << "\n=== EN-RU Dictionary ===\n"
              << "1. Add word\n"
              << "2. Find word\n"
              << "3. Remove word\n"
              << "4. List all\n"
              << "5. Search by Russian translation\n"
              << "6. Save\n"
              << "7. Load\n"
              << "8. Show word count\n"
              << "9. Clear All words\n"     
              << "0. Exit\n"
              << "Choice: ";
}
}

int main() {
    auto dict = std::make_shared<Dictionary>("main");
    DictionaryManager manager;
    manager.addDictionary(dict);

    const std::string dataFile = "data/sample_dictionary.txt";

    while (true) {
        printMenu();
        int choice = 0;
        if (!(std::cin >> choice)) break;
        std::cin.ignore();

        try {
            switch (choice) {
                case 1: {
                    std::string en, pos, tr;
                    std::cout << "English word: ";  std::getline(std::cin, en);
                    std::cout << "Part of speech: "; std::getline(std::cin, pos);
                    std::cout << "Translation: ";   std::getline(std::cin, tr);
                    DictionaryEntry entry(Word(en, partOfSpeechFromString(pos)), {tr});
                    dict->addEntry(entry);
                    std::cout << "Added.\n";
                    break;
                }
                case 2: {
                    std::string en;
                    std::cout << "English word: "; std::getline(std::cin, en);
                    auto r = dict->find(en);
                    if (r) std::cout << *r << '\n';
                    else   std::cout << "Not found.\n";
                    break;
                }
                case 3: {
                    std::string en;
                    std::cout << "English word: "; std::getline(std::cin, en);
                    std::cout << (dict->removeEntry(en) ? "Removed.\n" : "Not found.\n");
                    break;
                }
                case 4:
                    for (const auto& e : dict->getAll()) std::cout << e << '\n';
                    break;
                case 5: {
                    std::string ru;
                    std::cout << "Russian word: "; std::getline(std::cin, ru);
                    for (const auto& e : dict->findByTranslation(ru)) std::cout << e << '\n';
                    break;
                }
                case 6:
                    manager.saveToFile(dataFile, "main");
                    std::cout << "Saved.\n";
                    break;
                case 7:
                    manager.loadFromFile(dataFile, "main");
                    std::cout << "Loaded.\n";
                    break;
                case 8:
                    std::cout << "Total words: " << dict->size() << "\n";
                    break;
                case 9:
                    dict->clear();
                    std::cout << "All words cleared.\n";
                    break;
                case 0:
                    return 0;
                default:
                    std::cout << "Unknown option.\n";
            }
        } catch (const DictionaryException& e) {
            std::cerr << e.what() << '\n';
        }
    }
    return 0;
}
