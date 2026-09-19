#include <gtest/gtest.h>
#include "Word.h"

TEST(WordTest, Construction) {
    Word w("hello", PartOfSpeech::Noun);
    EXPECT_EQ(w.getText(), "hello");
    EXPECT_EQ(w.getPartOfSpeech(), PartOfSpeech::Noun);
}

TEST(WordTest, Equality) {
    EXPECT_EQ(Word("a", PartOfSpeech::Verb), Word("a", PartOfSpeech::Verb));
    EXPECT_NE(Word("a", PartOfSpeech::Verb), Word("a", PartOfSpeech::Noun));
}

TEST(WordTest, PartOfSpeechConversion) {
    EXPECT_EQ(partOfSpeechToString(PartOfSpeech::Noun), "noun");
    EXPECT_EQ(partOfSpeechFromString("verb"), PartOfSpeech::Verb);
    EXPECT_EQ(partOfSpeechFromString("xyz"), PartOfSpeech::Unknown);
}

TEST(WordTest, ToLower) {
    Word w("HELLO", PartOfSpeech::Noun);
    EXPECT_EQ(w.toLower(), "hello");
}
