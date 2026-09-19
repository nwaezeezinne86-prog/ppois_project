#include "Dictionary.h"
#include "Exceptions.h"
#include <algorithm>

Dictionary::Dictionary(std::string name) : name_(std::move(name)) {}

void Dictionary::addEntry(const DictionaryEntry& entry) {
    const auto& key = entry.getEnglish().getText();
    if (repository_.get(key).has_value()) {
        throw DuplicateWordException(key);
    }
    repository_.put(key, entry);
}

bool Dictionary::removeEntry(const std::string& englishWord) {
    return repository_.remove(englishWord);
}

std::optional<DictionaryEntry> Dictionary::find(const std::string& englishWord) const {
    return repository_.get(englishWord);
}

std::vector<DictionaryEntry> Dictionary::getAll() const {
    return repository_.all();
}

std::size_t Dictionary::size() const {
    return repository_.size();
}

void Dictionary::clear() {
    repository_.clear();
}

std::vector<DictionaryEntry> Dictionary::findByTranslation(const std::string& translation) const {
    std::vector<DictionaryEntry> result;
    for (const auto& entry : repository_.all()) {
        const auto& trs = entry.getTranslations();
        if (std::find(trs.begin(), trs.end(), translation) != trs.end()) {
            result.push_back(entry);
        }
    }
    return result;
}
