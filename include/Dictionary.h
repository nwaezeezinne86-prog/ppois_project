#pragma once
#include "IDictionary.h"
#include <map>

template<typename T>
class Repository {
public:
    void put(const std::string& key, const T& value) { store_[key] = value; }

    std::optional<T> get(const std::string& key) const {
        auto it = store_.find(key);
        if (it == store_.end()) return std::nullopt;
        return it->second;
    }

    bool remove(const std::string& key) { return store_.erase(key) > 0; }

    std::vector<T> all() const {
        std::vector<T> result;
        result.reserve(store_.size());
        for (const auto& [k, v] : store_) result.push_back(v);
        return result;
    }

    std::size_t size() const { return store_.size(); }
    void clear() { store_.clear(); }

private:
    std::map<std::string, T> store_;
};

class Dictionary : public IDictionary {
public:
    Dictionary() = default;
    explicit Dictionary(std::string name);

    void addEntry(const DictionaryEntry& entry) override;
    bool removeEntry(const std::string& englishWord) override;
    std::optional<DictionaryEntry> find(const std::string& englishWord) const override;

    std::vector<DictionaryEntry> getAll() const override;
    std::size_t size() const override;
    void clear() override;

    std::vector<DictionaryEntry> findByTranslation(const std::string& translation) const override;
    std::string getType() const override { return "BaseDictionary"; }
    const std::string& getName() const { return name_; }

private:
    std::string name_ = "default";
    Repository<DictionaryEntry> repository_;
};
