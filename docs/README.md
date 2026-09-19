# English-Russian Dictionary

![CI](https://github.com/nwaezeezinne86-prog/ppois_project/actions/workflows/ci.yml/badge.svg)

Console application for managing an English-Russian dictionary.

## Features
- Add, find, remove words
- Multiple translations per word
- Part of speech tagging
- Save/load from file
- Search by Russian translation
- Word count

## Tech Stack
- **C++17**, CMake, GoogleTest, GitHub Actions

## Build & Run
```bash
cmake -S . -B build
cmake --build build -j
cd build && ctest --output-on-failure
./dictionary_app
