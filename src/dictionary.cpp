#include "dictionary.hpp"

#include <algorithm>
#include <istream>
#include <ostream>

#include "text_utils.hpp"

namespace dict {

bool Dictionary::add(std::unique_ptr<Entry> entry) {
    if (!entry) return false;
    const std::string key = toLower(entry->english());
    const std::vector<std::string> russian = entry->russian();
    if (!entries_.add(key, std::move(entry))) return false;

    for (const auto& r : russian) {
        auto& keys = reverse_[toLower(r)];
        if (std::find(keys.begin(), keys.end(), key) == keys.end()) keys.push_back(key);
    }
    return true;
}

bool Dictionary::remove(const std::string& english) {
    const std::string key = toLower(trim(english));
    const Entry* entry = entries_.find(key);
    if (!entry) return false;

    for (const auto& r : entry->russian()) {
        const auto it = reverse_.find(toLower(r));
        if (it == reverse_.end()) continue;
        auto& keys = it->second;
        keys.erase(std::remove(keys.begin(), keys.end(), key), keys.end());
        if (keys.empty()) reverse_.erase(it);
    }
    return entries_.remove(key);
}

const Entry* Dictionary::toRussian(const std::string& english) const {
    return entries_.find(toLower(trim(english)));
}

std::vector<const Entry*> Dictionary::toEnglish(const std::string& russian) const {
    std::vector<const Entry*> result;
    const auto it = reverse_.find(toLower(trim(russian)));
    if (it == reverse_.end()) return result;
    for (const auto& key : it->second)
        if (const Entry* e = entries_.find(key)) result.push_back(e);
    return result;
}

std::vector<const Entry*> Dictionary::withPrefix(const std::string& prefix, std::size_t limit) const {
    return entries_.withPrefix(toLower(trim(prefix)), limit);
}

LoadResult Dictionary::load(std::istream& in) {
    LoadResult result;
    std::string line;
    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;
        if (add(Entry::parse(line))) ++result.loaded;
        else ++result.skipped;
    }
    return result;
}

void Dictionary::save(std::ostream& out) const {
    out << "# kind|english|russian;russian|extra\n";
    entries_.forEach([&out](const Entry& e) { out << e.serialize() << '\n'; });
}

}  // namespace dict
