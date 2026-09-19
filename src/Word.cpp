#include "Word.h"

std::string partOfSpeechToString(PartOfSpeech pos) {
    switch (pos) {
        case PartOfSpeech::Noun:        return "noun";
        case PartOfSpeech::Verb:        return "verb";
        case PartOfSpeech::Adjective:   return "adj";
        case PartOfSpeech::Adverb:      return "adv";
        case PartOfSpeech::Pronoun:     return "pron";
        case PartOfSpeech::Preposition: return "prep";
        case PartOfSpeech::Conjunction: return "conj";
        default:                        return "unknown";
    }
}

PartOfSpeech partOfSpeechFromString(const std::string& s) {
    if (s == "noun") return PartOfSpeech::Noun;
    if (s == "verb") return PartOfSpeech::Verb;
    if (s == "adj")  return PartOfSpeech::Adjective;
    if (s == "adv")  return PartOfSpeech::Adverb;
    if (s == "pron") return PartOfSpeech::Pronoun;
    if (s == "prep") return PartOfSpeech::Preposition;
    if (s == "conj") return PartOfSpeech::Conjunction;
    return PartOfSpeech::Unknown;
}

Word::Word(std::string text, PartOfSpeech pos)
    : text_(std::move(text)), pos_(pos) {}

bool Word::operator==(const Word& other) const {
    return text_ == other.text_ && pos_ == other.pos_;
}

bool Word::operator<(const Word& other) const {
    return text_ < other.text_;
}

bool Word::operator!=(const Word& other) const {
    return !(*this == other);
}
