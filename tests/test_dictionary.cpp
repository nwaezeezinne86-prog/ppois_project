#include <gtest/gtest.h>
#include "Dictionary.h"
#include "Exceptions.h"

class DictionaryTest : public ::testing::Test {
protected:
    Dictionary dict{"test"};
};

TEST_F(DictionaryTest, AddAndFind) {
    dict.addEntry(DictionaryEntry(Word("cat", PartOfSpeech::Noun), {"кошка", "кот"}));
    auto found = dict.find("cat");
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->getTranslations().size(), 2u);
}

TEST_F(DictionaryTest, DuplicateThrows) {
    DictionaryEntry e(Word("dog", PartOfSpeech::Noun), {"собака"});
    dict.addEntry(e);
    EXPECT_THROW(dict.addEntry(e), DuplicateWordException);
}

TEST_F(DictionaryTest, Remove) {
    dict.addEntry(DictionaryEntry(Word("cat", PartOfSpeech::Noun), {"кошка"}));
    EXPECT_TRUE(dict.removeEntry("cat"));
    EXPECT_FALSE(dict.removeEntry("cat"));
    EXPECT_EQ(dict.size(), 0u);
}

TEST_F(DictionaryTest, FindByTranslation) {
    dict.addEntry(DictionaryEntry(Word("cat", PartOfSpeech::Noun), {"кошка"}));
    dict.addEntry(DictionaryEntry(Word("pussycat", PartOfSpeech::Noun), {"кошка"}));
    auto results = dict.findByTranslation("кошка");
    EXPECT_EQ(results.size(), 2u);
}

TEST_F(DictionaryTest, Serialization) {
    DictionaryEntry original(Word("run", PartOfSpeech::Verb), {"бежать", "бегать"});
    auto restored = DictionaryEntry::deserialize(original.serialize());
    EXPECT_EQ(restored.getEnglish().getText(), "run");
    EXPECT_EQ(restored.getTranslations().size(), 2u);
}
