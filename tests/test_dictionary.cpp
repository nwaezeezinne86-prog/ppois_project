#include <sstream>

#include "dictionary.hpp"
#include "mini_test.hpp"
#include "text_utils.hpp"

using namespace dict;

// ---- text utils -----------------------------------------------------------
TEST(toLower_handles_ascii_and_cyrillic) {
    CHECK_EQ(toLower("Hello"), "hello");
    CHECK_EQ(toLower("ЯБЛОКО"), "яблоко");
    CHECK_EQ(toLower("Ёлка"), "ёлка");
    CHECK_EQ(toLower("Привет World"), "привет world");
}

TEST(trim_split_join) {
    CHECK_EQ(trim("  a b \t\n"), "a b");
    CHECK_EQ(split("a|b||c", '|').size(), 4u);
    CHECK_EQ(join({"x", "y", "z"}, ", "), "x, y, z");
}

// ---- entries (inheritance / polymorphism) --------------------------------
TEST(parse_builds_correct_subclasses) {
    CHECK_EQ(Entry::parse("noun|book|книга|f")->kind(), "noun");
    CHECK_EQ(Entry::parse("verb|read|читать|imperf")->kind(), "verb");
    CHECK_EQ(Entry::parse("adj|big|большой")->kind(), "adj");
    CHECK_EQ(Entry::parse("phrase|thank you|спасибо")->kind(), "phrase");
}

TEST(parse_rejects_malformed_lines) {
    CHECK(Entry::parse("") == nullptr);
    CHECK(Entry::parse("noun|book") == nullptr);
    CHECK(Entry::parse("noun||книга|f") == nullptr);
    CHECK(Entry::parse("noun|book| ; |f") == nullptr);
    CHECK(Entry::parse("spaceship|x|y") == nullptr);
}

TEST(virtual_format_differs_per_subclass) {
    std::unique_ptr<Entry> noun = std::make_unique<NounEntry>("book", std::vector<std::string>{"книга"}, 'f');
    std::unique_ptr<Entry> verb = std::make_unique<VerbEntry>("read", std::vector<std::string>{"читать"}, "imperf");
    CHECK(noun->format().find("feminine") != std::string::npos);
    CHECK(verb->format().find("imperfective") != std::string::npos);
}

TEST(serialize_parse_roundtrip) {
    const std::string line = "noun|cat|кошка;кот|f";
    CHECK_EQ(Entry::parse(line)->serialize(), line);
}

// ---- generic repository (templates) ---------------------------------------
TEST(repository_works_with_any_type) {
    Repository<int> repo;
    CHECK(repo.add("b", std::make_unique<int>(2)));
    CHECK(repo.add("a", std::make_unique<int>(1)));
    CHECK(!repo.add("a", std::make_unique<int>(9)));  // duplicate key
    CHECK_EQ(*repo.find("a"), 1);
    CHECK(repo.find("zzz") == nullptr);
    CHECK_EQ(repo.findIf([](int v) { return v > 1; }).size(), 1u);
    CHECK(repo.remove("a"));
    CHECK_EQ(repo.size(), 1u);
}

// ---- dictionary -----------------------------------------------------------
static Dictionary sample() {
    Dictionary d;
    d.add(Entry::parse("noun|cat|кошка;кот|f"));
    d.add(Entry::parse("noun|car|машина|f"));
    d.add(Entry::parse("noun|dog|собака;пёс|f"));
    d.add(Entry::parse("noun|friend|друг|m"));
    d.add(Entry::parse("noun|mate|друг|m"));
    return d;
}

TEST(english_to_russian_is_case_insensitive) {
    const Dictionary d = sample();
    const Entry* e = d.toRussian("  CaT ");
    CHECK(e != nullptr);
    CHECK_EQ(e->russian().size(), 2u);
    CHECK(d.toRussian("unicorn") == nullptr);
}

TEST(russian_to_english_returns_all_matches) {
    const Dictionary d = sample();
    CHECK_EQ(d.toEnglish("ДРУГ").size(), 2u);
    CHECK_EQ(d.toEnglish("пёс").size(), 1u);
    CHECK(d.toEnglish("пингвин").empty());
}

TEST(duplicate_and_null_entries_rejected) {
    Dictionary d = sample();
    CHECK(!d.add(Entry::parse("noun|CAT|кошка|f")));
    CHECK(!d.add(nullptr));
    CHECK_EQ(d.size(), 5u);
}

TEST(remove_cleans_reverse_index) {
    Dictionary d = sample();
    CHECK(d.remove("Dog"));
    CHECK(d.toRussian("dog") == nullptr);
    CHECK(d.toEnglish("собака").empty());
    CHECK(!d.remove("dog"));
    CHECK_EQ(d.toEnglish("друг").size(), 2u);  // untouched
}

TEST(prefix_search_respects_limit) {
    const Dictionary d = sample();
    CHECK_EQ(d.withPrefix("ca").size(), 2u);   // car, cat
    CHECK_EQ(d.withPrefix("ca", 1).size(), 1u);
    CHECK(d.withPrefix("x").empty());
}

TEST(load_skips_comments_blanks_and_bad_lines) {
    std::istringstream in("# comment\n\nnoun|cat|кошка|f\nbroken line\nnoun|cat|кот|m\n");
    Dictionary d;
    const LoadResult r = d.load(in);
    CHECK_EQ(r.loaded, 1u);
    CHECK_EQ(r.skipped, 2u);  // malformed + duplicate
}

TEST(save_then_load_roundtrip) {
    const Dictionary original = sample();
    std::stringstream buffer;
    original.save(buffer);
    Dictionary copy;
    CHECK_EQ(copy.load(buffer).loaded, original.size());
    CHECK_EQ(copy.toEnglish("друг").size(), 2u);
}

int main() { return mini::runAll(); }
