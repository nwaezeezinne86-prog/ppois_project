---
marp: true
theme: default
paginate: true
size: 16:9
---

# English-Russian Dictionary
### C++17 OOP Project

**Author:** nwaezeezinne86-prog
**Course:** PPOIS
**Date:** September 2026

---

## Goal

Build a command-line English-Russian dictionary
using modern C++17 and a professional Git workflow.

### Features
- Add / find / remove words
- Multiple translations per word
- Part-of-speech tagging
- Save / load from file
- Search by Russian translation
- Word count

---

## Tech Stack

- **Language:** C++17
- **Build:** CMake
- **Tests:** GoogleTest (13 tests)
- **CI:** GitHub Actions
- **VCS:** Git + GitHub PR workflow
- **Docs:** Markdown

---

## Architecture

main.cpp
│
DictionaryManager
│
IDictionary (abstract)
│
Dictionary ──uses──▶ Repository<T>
│
std::map<string, DictionaryEntry>
## OOP in Action

### Inheritance
```cpp
class Dictionary : public IDictionary { ... }; 
