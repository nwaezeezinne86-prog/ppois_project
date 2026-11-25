#include "entry.hpp"

#include "text_utils.hpp"

namespace dict {

Entry::Entry(std::string english, std::vector<std::string> russian)
    : english_(std::move(english)), russian_(std::move(russian)) {}

std::string Entry::format() const {
    return english_ + " [" + kind() + "] - " + join(russian_, ", ");
}

std::string Entry::serialize() const {
    return kind() + "|" + english_ + "|" + join(russian_, ";") + "|" + extra();
}

NounEntry::NounEntry(std::string en, std::vector<std::string> ru, char gender)
    : Entry(std::move(en), std::move(ru)), gender_(gender) {}

std::string NounEntry::format() const {
    std::string g;
    switch (gender_) {
        case 'm': g = "masculine"; break;
        case 'f': g = "feminine"; break;
        case 'n': g = "neuter"; break;
        default:  g = "gender n/a"; break;
    }
    return Entry::format() + " (" + g + ")";
}

VerbEntry::VerbEntry(std::string en, std::vector<std::string> ru, std::string aspect)
    : Entry(std::move(en), std::move(ru)), aspect_(std::move(aspect)) {}

std::string VerbEntry::format() const {
    if (aspect_ == "perf") return Entry::format() + " (perfective)";
    if (aspect_ == "imperf") return Entry::format() + " (imperfective)";
    return Entry::format();
}

std::unique_ptr<Entry> Entry::parse(const std::string& line) {
    const auto fields = split(line, '|');
    if (fields.size() < 3) return nullptr;

    const std::string kind = toLower(trim(fields[0]));
    const std::string en = trim(fields[1]);
    std::vector<std::string> ru;
    for (const auto& r : split(fields[2], ';')) {
        const std::string t = trim(r);
        if (!t.empty()) ru.push_back(t);
    }
    const std::string extra = fields.size() > 3 ? trim(fields[3]) : "";
    if (en.empty() || ru.empty()) return nullptr;

    if (kind == "noun")   return std::make_unique<NounEntry>(en, ru, extra.empty() ? '-' : extra[0]);
    if (kind == "verb")   return std::make_unique<VerbEntry>(en, ru, extra);
    if (kind == "adj")    return std::make_unique<AdjectiveEntry>(en, ru);
    if (kind == "phrase") return std::make_unique<PhraseEntry>(en, ru);
    return nullptr;
}

}  // namespace dict
