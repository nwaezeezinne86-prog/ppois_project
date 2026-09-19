#pragma once
#include "Word.h"
#include <vector>
#include <string>
#include <ostream>

class DictionaryEntry {
public:
    DictionaryEntry() = default;
    DictionaryEntry(Word english, std::vector<std::string> translations);

    const Word& getEnglish() const { return english_; }
    const std::vector<std::string>& getTranslations() const { return translations_; }

    void addTranslation(const std::string& translation);
    bool removeTranslation(const std::string& translation);

    std::string serialize() const;
    static DictionaryEntry deserialize(const std::string& line);

    friend std::ostream& operator<<(std::ostream& os, const DictionaryEntry& entry);

private:
    Word english_;
    std::vector<std::string> translations_;
};
