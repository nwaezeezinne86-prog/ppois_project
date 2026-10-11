
# Англо-русский словарь
# English-Russian Dictionary

---

## Основные характеристики / Main Characteristics

| Параметр / Parameter | Значение / Value |
|---|---|
| **Язык программирования** / Language | C++17 |
| **Среда разработки** / IDE | VS Code, WSL (Ubuntu 24.04), CLion |
| **Тип проекта** / Project type | Консольное приложение + статическая библиотека / Console app + static library |
| **Система сборки** / Build system | CMake 3.15+ |
| **Тестирование** / Testing | GoogleTest |
| **CI/CD** | GitHub Actions |
| **Контроль версий** / Version control | Git + GitHub Pull Requests |

---

## Состав проекта / Project Composition

1. **Иерархия классов** — слова, словарные статьи, словари  
   **Class hierarchy** — words, dictionary entries, dictionaries
2. **Шаблонный контейнер** — `Repository<T>` для обобщённого хранения  
   **Generic container** — `Repository<T>` template for storage
3. **Менеджер словарей** — управление и файловый ввод-вывод  
   **Dictionary manager** — orchestration and file I/O
4. **Приложение** — консольный интерфейс + логика команд  
   **Application** — console interface + command logic
5. **Модульные тесты** — 13 тестов в 3 наборах  
   **Unit tests** — 13 tests across 3 suites
6. **Непрерывная интеграция** — конвейер GitHub Actions  
   **Continuous Integration** — GitHub Actions pipeline

---

## Задачи разработки / Development Tasks

- ✅ **Парсинг данных** и загрузка из текстового файла в память  
  **Parsing data** and loading from text file into memory
- ✅ **Иерархия классов** (инкапсуляция, наследование, полиморфизм)  
  **Class hierarchy** (encapsulation, inheritance, polymorphism)
- ✅ **Правила модели** для поиска слова по входным данным  
  **Model rules** for finding a word by input data
- ✅ **Вывод списка** подходящих слов с указанием части речи  
  **Display list** of matching words with parts of speech
- ✅ **Поиск слова** и получение всей информации о нём  
  **Search** for a word and retrieve all information
- ✅ **Методы и обработчики** команд пользователя  
  **Methods and handlers** for user commands
- ✅ **Консольный интерфейс** приложения  
  **Console interface** for the application
- ✅ **Тестирование** с использованием GoogleTest  
  **Testing** with GoogleTest
- ✅ **Автоматическая сборка и тестирование** через GitHub Actions  
  **Automatic build and test** via GitHub Actions

---

## Используемые технологии / Technologies Used

| Технология / Technology | Назначение / Purpose |
|---|---|
| **ООП** / OOP | инкапсуляция, наследование, полиморфизм / encapsulation, inheritance, polymorphism |
| **Шаблоны C++** / C++ Templates | обобщённое программирование (`Repository<T>`) / generic programming |
| **STL** | `std::map`, `std::vector`, `std::optional`, `std::shared_ptr`, алгоритмы / algorithms |
| **CMake** | кроссплатформенная сборка / cross-platform build |
| **GoogleTest** | модульное тестирование / unit testing |
| **GitHub Actions** | непрерывная интеграция (CI) / continuous integration |
| **Doxygen** | документация API / API documentation |
| **Markdown** | документация проекта / project documentation |
| **Git** | контроль версий и Pull Requests / version control and PRs |

---

## Логика работы программы / Program Logic

### Входные данные / Input Data

Приложение предоставляет интерактивное меню:  
The application provides an interactive menu:

