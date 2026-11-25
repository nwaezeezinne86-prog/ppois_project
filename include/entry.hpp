#pragma once
#include <memory>
#include <string>
#include <vector>

namespace dict {

// Abstract base class of every dictionary entry (inheritance + polymorphism).
class Entry {
public:
    Entry(std::string english, std::vector<std::string> russian);
    virtual ~Entry() = default;

    virtual std::string kind() const = 0;           // "noun", "verb", ...
    virtual std::string format() const;             // human-readable text
    std::string serialize() const;                  // kind|english|ru1;ru2|extra

    const std::string& english() const { return english_; }
    const std::vector<std::string>& russian() const { return russian_; }

    // Factory: builds the right subclass from one serialized line (nullptr if malformed).
    static std::unique_ptr<Entry> parse(const std::string& line);

protected:
    virtual std::string extra() const { return ""; }  // kind-specific serialized field

private:
    std::string english_;
    std::vector<std::string> russian_;
};

class NounEntry final : public Entry {
public:
    NounEntry(std::string en, std::vector<std::string> ru, char gender = '-');
    std::string kind() const override { return "noun"; }
    std::string format() const override;
    char gender() const { return gender_; }

protected:
    std::string extra() const override { return std::string(1, gender_); }

private:
    char gender_;  // m / f / n / - (unknown)
};

class VerbEntry final : public Entry {
public:
    VerbEntry(std::string en, std::vector<std::string> ru, std::string aspect = "");
    std::string kind() const override { return "verb"; }
    std::string format() const override;
    const std::string& aspect() const { return aspect_; }

protected:
    std::string extra() const override { return aspect_; }

private:
    std::string aspect_;  // "perf" / "imperf" / ""
};

class AdjectiveEntry final : public Entry {
public:
    using Entry::Entry;
    std::string kind() const override { return "adj"; }
};

class PhraseEntry final : public Entry {
public:
    using Entry::Entry;
    std::string kind() const override { return "phrase"; }
};

}  // namespace dict
