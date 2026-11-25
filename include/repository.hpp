#pragma once
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace dict {

// Generic ordered key -> owned-object store (template). Keys are kept sorted,
// so prefix search is a lower_bound + scan.
template <typename T>
class Repository {
public:
    bool add(const std::string& key, std::unique_ptr<T> item) {
        if (!item || items_.count(key)) return false;
        items_.emplace(key, std::move(item));
        return true;
    }

    const T* find(const std::string& key) const {
        const auto it = items_.find(key);
        return it == items_.end() ? nullptr : it->second.get();
    }

    bool remove(const std::string& key) { return items_.erase(key) > 0; }

    std::size_t size() const { return items_.size(); }
    bool empty() const { return items_.empty(); }

    std::vector<const T*> withPrefix(
        const std::string& prefix,
        std::size_t limit = std::numeric_limits<std::size_t>::max()) const {
        std::vector<const T*> out;
        for (auto it = items_.lower_bound(prefix); it != items_.end() && out.size() < limit; ++it) {
            if (it->first.compare(0, prefix.size(), prefix) != 0) break;
            out.push_back(it->second.get());
        }
        return out;
    }

    template <typename Pred>
    std::vector<const T*> findIf(Pred pred) const {
        std::vector<const T*> out;
        for (const auto& kv : items_)
            if (pred(*kv.second)) out.push_back(kv.second.get());
        return out;
    }

    template <typename F>
    void forEach(F f) const {
        for (const auto& kv : items_) f(*kv.second);
    }

private:
    std::map<std::string, std::unique_ptr<T>> items_;
};

}  // namespace dict
