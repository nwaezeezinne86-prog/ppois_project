#include "DictionaryEntry.h"
#include <algorithm>
#include <sstream>

DictionaryEntry::DictionaryEntry(Word english, std::vector<std::string> translations)
    : english_(std::move(english)), translations_(std::move(translations)) {}

void DictionaryEntry::addTranslation(const std::string& t) {
    if (std::find(translations_.begin(), translations_.end(), t) == translations_.end()) {
        translations_.push_back(t);
    }
}

bool DictionaryEntry::removeTranslation(const std::string& t) {
    auto it = std::find(translations_.begin(), translations_.end(), t);
    if (it == translations_.end()) return false;
    translations_.erase(it);
    return true;
}

std::string DictionaryEntry::serialize() const {
    std::ostringstream oss;
    oss << english_.getText() << "|"
        << partOfSpeechToString(english_.getPartOfSpeech()) << "|";
    for (std::size_t i = 0; i < translations_.size(); ++i) {
        if (i) oss << ";";
        oss << translations_[i];
    }
    return oss.str();
}

DictionaryEntry DictionaryEntry::deserialize(const std::string& line) {
    std::istringstream iss(line);
    std::string word, posStr, transStr;
    std::getline(iss, word, '|');
    std::getline(iss, posStr, '|');
    std::getline(iss, transStr);

    std::vector<std::string> translations;
    std::istringstream tStream(transStr);
    std::string t;
    while (std::getline(tStream, t, ';')) {
        if (!t.empty()) translations.push_back(t);
    }
    return DictionaryEntry(Word(word, partOfSpeechFromString(posStr)), translations);
}

std::ostream& operator<<(std::ostream& os, const DictionaryEntry& entry) {
    os << entry.english_.getText()
       << " [" << partOfSpeechToString(entry.english_.getPartOfSpeech()) << "] -> ";
    for (std::size_t i = 0; i < entry.translations_.size(); ++i) {
        if (i) os << ", ";
        os << entry.translations_[i];
    }
    return os;
}
