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

- **Наследование**: классы `NounEntry`, `VerbEntry`, `AdjectiveEntry` и `PhraseEntry` наследуются от абстрактного класса `Entry`.
- **Полиморфизм**: метод `kind()` является чисто виртуальным; методы `format()` и `extra()` переопределены в каждом подклассе. Класс `Dictionary` работает исключительно с указателями типа `Entry*`, а статический метод `Entry::parse` выступает в роли фабрики, возвращающей `std::unique_ptr<Entry>`.
- **Шаблоны**: `Repository<T>` представляет собой универсальный контейнер, владеющий своими элементами (поддерживает операции добавления, поиска, удаления, а также методы `withPrefix`, `findIf` и `forEach`). В тестах используется экземпляр `Repository<int>`, что подтверждает его универсальность.
- **STL**: используются `std::map` (для хранения отсортированных ключей и поиска по префиксу), `std::unordered_map` (для создания обратного индекса «русский — английский»), `std::vector`, `std::unique_ptr`, алгоритмы `std::find` и `std::remove`, а также потоки ввода-вывода.

## Design decisions

- Keys are lower-cased; a custom `toLower` handles Cyrillic UTF-8 (no locale dependency).
- Russian→English uses a reverse index, so lookups are O(1) average instead of scanning all entries.
- Ownership: `Repository` owns entries via `unique_ptr`; callers receive non-owning `const Entry*`.
- Malformed lines are skipped and counted (`LoadResult`), never crash the program.

- Ключи приводятся к нижнему регистру; для этого используется собственная функция `toLower`, корректно обрабатывающая кириллицу в кодировке UTF-8 (без привязки к локали).
- При поиске с русского на английский используется обратный индекс, что обеспечивает среднюю сложность операций O(1) вместо перебора всех записей.
- Владение: объект `Repository` владеет записями через `unique_ptr`; внешнему коду предоставляются указатели `const Entry*`, не подразумевающие владения.
- Некорректные строки пропускаются и учитываются в статистике (`LoadResult`); программа при их обнаружении не завершается аварийно.
