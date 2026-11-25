# English–Russian Dictionary (C++17)

A console English⇄Russian dictionary built in C++ with inheritance, polymorphism, templates and the STL.

## Requirements checklist

| Requirement | Where it is covered |
|---|---|
| Max 3 people per project | Team of 3, roles in [CONTRIBUTING.md](CONTRIBUTING.md) |
| GitHub + pull requests, history, iterative work | Branch-per-task + PR template, `.github/` |
| Project documentation in MD files | `README.md`, `CONTRIBUTING.md`, `docs/*.md` |
| Mandatory unit testing | `tests/test_dictionary.cpp` (14 tests), run in CI |
| Task board | [docs/BOARD.md](docs/BOARD.md) (mirror in GitHub Projects) |
| Detailed report + defense presentation | [docs/REPORT.md](docs/REPORT.md) + slides |
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
