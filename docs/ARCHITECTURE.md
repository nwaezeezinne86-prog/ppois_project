# Architecture

## Layers

main.cpp (CLI)
│
DictionaryManager (orchestration + file I/O)
│
IDictionary (abstract interface)
│
Dictionary (concrete implementation)
│
Repository<T> (generic map-backed storage)

## Classes

| Class | Role |
|---|---|
| `Word` | English text + PartOfSpeech enum |
| `DictionaryEntry` | Word + list of Russian translations |
| `Repository<T>` | Template: generic `std::map` wrapper |
| `IDictionary` | Abstract interface (pure virtual) |
| `Dictionary` | Concrete dictionary |
| `DictionaryManager` | Owns multiple dictionaries, save/load |
| `DictionaryException` | Base exception |

## OOP Principles

### Inheritance
- `class Dictionary : public IDictionary`
- `DuplicateWordException : DictionaryException : std::runtime_error`

### Polymorphism
- `IDictionary` declares virtual methods
- `DictionaryManager` stores `std::vector<std::shared_ptr<IDictionary>>`
- `dynamic_pointer_cast<Dictionary>` retrieves concrete type

### Templates
- `Repository<T>` — reusable generic key-value store

### STL
- `std::map` — word storage
- `std::vector` — translations and search results
- `std::optional` — safe "not found" return
- `std::shared_ptr` — ownership
- `std::istringstream` — parsing
- `std::find`, `std::transform` — algorithms

## File Format

<english>|<pos>|<translation1>;<translation2>;...
Example:
cat|noun|кошка;кот
run|verb|бежать;бегать
