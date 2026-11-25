#pragma once
#include <iosfwd>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "entry.hpp"
#include "repository.hpp"

namespace dict {

struct LoadResult {
    std::size_t loaded = 0;
    std::size_t skipped = 0;
};

class Dictionary {
public:
    bool add(std::unique_ptr<Entry> entry);            // false if null or duplicate
    bool remove(const std::string& english);

    const Entry* toRussian(const std::string& english) const;
    std::vector<const Entry*> toEnglish(const std::string& russian) const;
    std::vector<const Entry*> withPrefix(const std::string& prefix, std::size_t limit = 10) const;

    std::size_t size() const { return entries_.size(); }

    LoadResult load(std::istream& in);                 // '#' comments and blank lines ignored
    void save(std::ostream& out) const;

    template <typename F>
    void forEach(F f) const { entries_.forEach(f); }

private:
    Repository<Entry> entries_;                                          // en (lower) -> entry
    std::unordered_map<std::string, std::vector<std::string>> reverse_;  // ru (lower) -> en keys
};

}  // namespace dict
