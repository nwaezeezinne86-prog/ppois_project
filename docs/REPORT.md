# Project report: English–Russian Dictionary

## 1. Goal and scope
Console dictionary for EN⇄RU lookup, prefix search and editable data stored in a text file.
Консольный словарь для поиска по английскому языку EN⇄RU, поиска по префиксам и редактирования данных, хранящихся в текстовом файле.

## 2. Team and process
Three members, roles in `CONTRIBUTING.md`. Work through GitHub: branches, pull requests, review, CI. Iterations: (1) model, (2) storage + lookup, (3) CLI, (4) tests and docs.
Три участника, роли описаны в `CONTRIBUTING.md`. Работа через GitHub: ветки, пул-реквесты, код-ревью, CI. Итерации: (1) модель, (2) хранилище и поиск, (3) интерфейс командной строки (CLI), (4) тесты и документация.

## 3. Architecture
See `docs/ARCHITECTURE.md` (class diagram, concepts used).
См. `docs/ARCHITECTURE.md` (диаграмма классов, используемые концепции).

## 4. Implementation details
- Entry hierarchy and factory parsing
- `Repository<T>` template
- Reverse index for RU→EN
- UTF-8 Cyrillic lower-casing
- Иерархия записей и фабричный механизм разбора
- Шаблон `Repository<T>`
- Обратный индекс для направления RU→EN
- Приведение кириллических символов к нижнему регистру (UTF-8)

## 5. Testing
14 unit tests: text utils, parsing, polymorphic formatting, repository, dictionary operations, load/save round trip. Run with CTest and in GitHub Actions.
14 модульных тестов: вспомогательные функции для работы с текстом, синтаксический разбор, полиморфное форматирование, репозиторий, операции со словарями, проверка цикла «загрузка — сохранение». Запуск с помощью CTest и в GitHub Actions.

## 6. Results
Insert screenshots of the CLI session and the passing test run.
Вставьте скриншоты сеанса CLI и успешного выполнения теста.

## 7. Problems and solutions
- Case-insensitive Russian search without locales → custom `toLower`.
- Ambiguous Russian words (друг → friend, mate) → reverse index stores a list.
- Поиск по русскому тексту без учета регистра и без использования локалей → реализован собственный метод `toLower`.
- Многозначные русские слова (например, «друг» → friend, mate) → в обратном индексе для каждого слова хранится список значений.

## 8. Conclusions and future work
Fuzzy search, quiz mode, larger imported dictionaries, GUI.
Нечеткий поиск, режим викторины, поддержка более объемных импортированных словарей, графический интерфейс.
