#include "DictionaryManager.h"
#include "Dictionary.h"
#include "Exceptions.h"
#include <fstream>

void DictionaryManager::addDictionary(std::shared_ptr<IDictionary> dict) {
    dictionaries_.push_back(std::move(dict));
}

std::shared_ptr<IDictionary> DictionaryManager::getDictionary(const std::string& name) const {
    for (const auto& d : dictionaries_) {
        auto concrete = std::dynamic_pointer_cast<Dictionary>(d);
        if (concrete && concrete->getName() == name) return d;
    }
    return nullptr;
}

void DictionaryManager::saveToFile(const std::string& path, const std::string& dictName) const {
    auto dict = getDictionary(dictName);
    if (!dict) throw DictionaryException("Dictionary not found: " + dictName);

    std::ofstream out(path);
    if (!out) throw FileIOException(path);

    for (const auto& entry : dict->getAll()) {
        out << entry.serialize() << '\n';
    }
}

void DictionaryManager::loadFromFile(const std::string& path, const std::string& dictName) {
    auto dict = getDictionary(dictName);
    if (!dict) throw DictionaryException("Dictionary not found: " + dictName);

    std::ifstream in(path);
    if (!in) throw FileIOException(path);

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        dict->addEntry(DictionaryEntry::deserialize(line));
    }
}

std::vector<DictionaryEntry> DictionaryManager::searchAll(const std::string& englishWord) const {
    std::vector<DictionaryEntry> result;
    for (const auto& d : dictionaries_) {
        auto found = d->find(englishWord);
        if (found) result.push_back(*found);
    }
    return result;
}
