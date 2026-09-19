#pragma once
#include "IDictionary.h"
#include <memory>
#include <vector>
#include <string>

class DictionaryManager {
public:
    DictionaryManager() = default;

    void addDictionary(std::shared_ptr<IDictionary> dict);
    std::shared_ptr<IDictionary> getDictionary(const std::string& name) const;

    void saveToFile(const std::string& path, const std::string& dictName) const;
    void loadFromFile(const std::string& path, const std::string& dictName);

    std::vector<DictionaryEntry> searchAll(const std::string& englishWord) const;
    std::size_t getDictionaryCount() const { return dictionaries_.size(); }

private:
    std::vector<std::shared_ptr<IDictionary>> dictionaries_;
};
