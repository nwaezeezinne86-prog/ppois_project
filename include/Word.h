




#pragma once
#include <string>

enum class PartOfSpeech {
    Noun, Verb, Adjective, Adverb, Pronoun,
    Preposition, Conjunction, Unknown
};

std::string partOfSpeechToString(PartOfSpeech pos);
PartOfSpeech partOfSpeechFromString(const std::string& s);

class Word {
public:
    Word() = default;
    Word(std::string text, PartOfSpeech pos = PartOfSpeech::Unknown);

    const std::string& getText() const { return text_; }
    PartOfSpeech getPartOfSpeech() const { return pos_; }

    void setText(const std::string& t) { text_ = t; }
    void setPartOfSpeech(PartOfSpeech p) { pos_ = p; }

    bool operator==(const Word& other) const;
    bool operator!=(const Word& other) const;
    bool operator<(const Word& other) const;

private:
    std::string text_;
    PartOfSpeech pos_ = PartOfSpeech::Unknown;
};
