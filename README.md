# English–Russian Dictionary 

A console application that stores and queries an English⇄Russian  dictionary.
Entries are loaded from a text file, can be searched in both directions,
and the data can be saved back to disk. The project demonstrates core C++
concepts (inheritance, polymorphism, templates, STL) and a professional
development workflow (Git, Pull Requests, CI, documentation).
Консольное приложение для хранения англо-русского/русско-английского словаря и поиска в нём.
Словарные статьи загружаются из текстового файла, поиск возможен в обоих направлениях,
а данные можно сохранить обратно на диск. Проект демонстрирует ключевые концепции C++
(наследование, полиморфизм, шаблоны, STL) и профессиональный процесс разработки
(Git, pull-реквесты, CI, документация).

## Requirements checklist

| Requirement | Where it is covered |
|---|---|
| Roles| roles in [CONTRIBUTING.md](CONTRIBUTING.md) |
| GitHub + pull requests, history, iterative work | Branch-per-task + PR template, `.github/` |
| Project documentation in MD files | `README.md`, `CONTRIBUTING.md`, `docs/*.md` |
| Mandatory unit testing | `tests/test_dictionary.cpp` (14 tests), run in CI |
| Task board | [docs/BOARD.md](docs/BOARD.md) (mirror in GitHub Projects) |
| Detailed report  | [docs/REPORT.md](docs/REPORT.md) |
| Inheritance, polymorphism, templates, STL | See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) |
| Language: C++ | C++17, no external dependencies |

## Build and run

```bash
# CMake
cmake -S . -B build && cmake --build build
ctest --test-dir build --output-on-failure
./build/dictionary data/dictionary.txt

# or plain g++
g++ -std=c++17 -Iinclude src/*.cpp -o dictionary && ./dictionary data/dictionary.txt
g++ -std=c++17 -Iinclude src/text_utils.cpp src/entry.cpp src/dictionary.cpp tests/test_dictionary.cpp -o run_tests && ./run_tests
```

## Commands

| Command | Action |
|---|---|
| `en <word>` | English → Russian |
| `ru <слово>` | Russian → English (all matches) |
| `find <prefix>` | Autocomplete English words |
| `add noun\|word\|слово\|m` | Add an entry |
| `del <word>` | Delete an entry |
| `list`, `stats`, `save`, `help`, `quit` | Utilities |

## Data format (`data/dictionary.txt`)

`kind|english|russian1;russian2|extra`, where kind is `noun` (extra = gender m/f/n), `verb` (extra = perf/imperf), `adj` or `phrase`. Lines starting with `#` are comments. The file is UTF-8.
