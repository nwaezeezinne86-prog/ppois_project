#pragma once
#include "DictionaryEntry.h"
#include <string>
#include <vector>
#include <optional>

class IDictionary {
public:
    virtual ~IDictionary() = default;

    virtual void addEntry(const DictionaryEntry& entry) = 0;
    virtual bool removeEntry(const std::string& englishWord) = 0;
    virtual std::optional<DictionaryEntry> find(const std::string& englishWord) const = 0;

    virtual std::vector<DictionaryEntry> getAll() const = 0;
    virtual std::size_t size() const = 0;
    virtual void clear() = 0;

    virtual std::vector<DictionaryEntry> findByTranslation(const std::string& translation) const = 0;
    virtual std::string getType() const = 0;
};
