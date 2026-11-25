# Architecture

```
main.cpp (CLI)  ->  Dictionary  ->  Repository<Entry>  (template, std::map)
                        |                 ^
                        |                 owns
                        v                 |
                  reverse index      Entry (abstract)
                (unordered_map)   /     |       |       \
                          NounEntry VerbEntry AdjectiveEntry PhraseEntry
```

## Required C++ concepts

- **Inheritance**: `NounEntry`, `VerbEntry`, `AdjectiveEntry`, `PhraseEntry` derive from the abstract `Entry`.
- **Polymorphism**: `kind()` is pure virtual; `format()` and `extra()` are overridden per subclass. `Dictionary` only works with `Entry*`; `Entry::parse` is a factory returning `std::unique_ptr<Entry>`.
- **Templates**: `Repository<T>` is a generic owning store (add / find / remove / `withPrefix` / `findIf` / `forEach`). Tests instantiate it with `int` to prove it is generic.
- **STL**: `std::map` (sorted keys, prefix search), `std::unordered_map` (Russian→English reverse index), `std::vector`, `std::unique_ptr`, `std::find`, `std::remove`, streams.

## Design decisions

- Keys are lower-cased; a custom `toLower` handles Cyrillic UTF-8 (no locale dependency).
- Russian→English uses a reverse index, so lookups are O(1) average instead of scanning all entries.
- Ownership: `Repository` owns entries via `unique_ptr`; callers receive non-owning `const Entry*`.
- Malformed lines are skipped and counted (`LoadResult`), never crash the program.
