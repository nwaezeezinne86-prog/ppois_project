# English-Russian Dictionary

![CI](https://github.com/nwaezeezinne86-prog/ppois_project/actions/workflows/ci.yml/badge.svg)

A console application for managing an English-Russian dictionary, written in modern C++17.

## Features

- Add, find, and remove words
- Multiple translations per word
- Part-of-speech tagging (noun, verb, adj, adv, ...)
- Save and load from file
- Search by Russian translation
- Word count

## Tech Stack

- **C++17** — language standard
- **CMake** — cross-platform build
- **GoogleTest** — unit testing (13 tests)
- **GitHub Actions** — CI pipeline

## Build & Run

```bash
# Configure
cmake -S . -B build

# Build
cmake --build build -j

# Run tests
cd build && ctest --output-on-failure

# Run the app
./dictionary_app
