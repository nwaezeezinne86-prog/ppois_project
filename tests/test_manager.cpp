#include <gtest/gtest.h>
#include "DictionaryManager.h"
#include "Dictionary.h"
#include <cstdio>

TEST(ManagerTest, AddAndGet) {
    DictionaryManager mgr;
    auto d = std::make_shared<Dictionary>("main");
    mgr.addDictionary(d);
    EXPECT_EQ(mgr.getDictionaryCount(), 1u);
    EXPECT_NE(mgr.getDictionary("main"), nullptr);
    EXPECT_EQ(mgr.getDictionary("other"), nullptr);
}

TEST(ManagerTest, SearchAcrossDictionaries) {
    DictionaryManager mgr;
    auto d1 = std::make_shared<Dictionary>("d1");
    auto d2 = std::make_shared<Dictionary>("d2");
    d1->addEntry(DictionaryEntry(Word("cat", PartOfSpeech::Noun), {"кошка"}));
    d2->addEntry(DictionaryEntry(Word("cat", PartOfSpeech::Noun), {"кот"}));
    mgr.addDictionary(d1);
    mgr.addDictionary(d2);
    EXPECT_EQ(mgr.searchAll("cat").size(), 2u);
}

TEST(ManagerTest, SaveAndLoad) {
    const std::string path = "test_dict_tmp.txt";
    DictionaryManager mgr;
    auto d = std::make_shared<Dictionary>("main");
    d->addEntry(DictionaryEntry(Word("tree", PartOfSpeech::Noun), {"дерево"}));
    mgr.addDictionary(d);
    mgr.saveToFile(path, "main");

    auto d2 = std::make_shared<Dictionary>("main");
    DictionaryManager mgr2;
    mgr2.addDictionary(d2);
    mgr2.loadFromFile(path, "main");
    EXPECT_EQ(d2->size(), 1u);
    std::remove(path.c_str());
}
