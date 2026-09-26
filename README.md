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

---

## 🇷🇺 Русское описание

### Англо-русский словарь

Консольное приложение для управления англо-русским словарём, написанное на современном C++17.

### Возможности

- **Добавление слов** — с одним или несколькими русскими переводами
- **Поиск** — по английскому слову или по русскому переводу
- **Удаление** — удаление слов из словаря
- **Часть речи** — существительное, глагол, прилагательное, наречие, местоимение, предлог, союз
- **Сохранение и загрузка** — из текстового файла
- **Подсчёт слов** — общее количество записей в словаре
- **Очистка словаря** — удалить все слова сразу

### Технологии

| Технология | Назначение |
|---|---|
| **C++17** | Язык программирования |
| **CMake** | Система сборки |
| **GoogleTest** | Модульное тестирование (13 тестов) |
| **GitHub Actions** | Непрерывная интеграция (CI) |
| **Git** | Контроль версий |
| **Markdown** | Документация |

### Принципы ООП

- **Наследование** — `Dictionary : public IDictionary`
- **Полиморфизм** — виртуальные методы `IDictionary`, `std::shared_ptr<IDictionary>`
- **Шаблоны** — класс `Repository<T>` для обобщённого хранения
- **STL** — `std::map`, `std::vector`, `std::optional`, `std::shared_ptr`, алгоритмы

### Сборка и запуск

```bash
# Клонирование репозитория
git clone git@github.com:nwaezeezinne86-prog/ppois_project.git
cd ppois_project

# Конфигурация
cmake -S . -B build

# Сборка
cmake --build build -j

# Запуск тестов
cd build && ctest --output-on-failure

# Запуск приложения
./dictionary_app
