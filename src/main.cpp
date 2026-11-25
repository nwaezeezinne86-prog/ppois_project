#include <fstream>
#include <iostream>
#include <map>

#include "dictionary.hpp"
#include "text_utils.hpp"

using namespace dict;

static void printHelp() {
    std::cout <<
        "Commands:\n"
        "  en <word>        translate English -> Russian\n"
        "  ru <слово>       translate Russian -> English\n"
        "  find <prefix>    English words starting with prefix\n"
        "  add <kind>|<english>|<ru1;ru2>|<extra>   (kind: noun, verb, adj, phrase)\n"
        "  del <word>       delete an English entry\n"
        "  list | stats | save | help | quit\n";
}

int main(int argc, char** argv) {
    const std::string path = argc > 1 ? argv[1] : "data/dictionary.txt";
    Dictionary dictionary;

    std::ifstream in(path);
    if (in) {
        const LoadResult r = dictionary.load(in);
        std::cout << "Loaded " << r.loaded << " entries (" << r.skipped << " skipped) from " << path << "\n";
    } else {
        std::cout << "No file at " << path << ", starting with an empty dictionary.\n";
    }
    printHelp();

    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line)) {
        line = trim(line);
        if (line.empty()) continue;
        const auto space = line.find(' ');
        const std::string cmd = toLower(line.substr(0, space));
        const std::string arg = space == std::string::npos ? "" : trim(line.substr(space + 1));

        if (cmd == "quit" || cmd == "exit") break;

        if (cmd == "en") {
            const Entry* e = dictionary.toRussian(arg);
            std::cout << (e ? e->format() : "Not found.") << "\n";
        } else if (cmd == "ru") {
            const auto found = dictionary.toEnglish(arg);
            if (found.empty()) std::cout << "Not found.\n";
            for (const Entry* e : found) std::cout << e->format() << "\n";
        } else if (cmd == "find") {
            const auto found = dictionary.withPrefix(arg, 20);
            if (found.empty()) std::cout << "No matches.\n";
            for (const Entry* e : found) std::cout << "  " << e->english() << "\n";
        } else if (cmd == "add") {
            std::cout << (dictionary.add(Entry::parse(arg)) ? "Added." : "Invalid line or duplicate.") << "\n";
        } else if (cmd == "del") {
            std::cout << (dictionary.remove(arg) ? "Deleted." : "Not found.") << "\n";
        } else if (cmd == "list") {
            dictionary.forEach([](const Entry& e) { std::cout << e.format() << "\n"; });
        } else if (cmd == "stats") {
            std::map<std::string, std::size_t> counts;
            dictionary.forEach([&counts](const Entry& e) { ++counts[e.kind()]; });
            std::cout << "Total: " << dictionary.size() << "\n";
            for (const auto& kv : counts) std::cout << "  " << kv.first << ": " << kv.second << "\n";
        } else if (cmd == "save") {
            std::ofstream out(path);
            if (out) { dictionary.save(out); std::cout << "Saved to " << path << ".\n"; }
            else std::cout << "Cannot write " << path << ".\n";
        } else if (cmd == "help") {
            printHelp();
        } else {
            std::cout << "Unknown command. Type 'help'.\n";
        }
    }
    return 0;
}
