#pragma once
#include <stdexcept>
#include <string>

class DictionaryException : public std::runtime_error {
public:
    explicit DictionaryException(const std::string& msg)
        : std::runtime_error("[Error] " + msg) {}
};

class WordNotFoundException : public DictionaryException {
public:
    explicit WordNotFoundException(const std::string& word)
        : DictionaryException("Word not found: " + word) {}
};

class DuplicateWordException : public DictionaryException {
public:
    explicit DuplicateWordException(const std::string& word)
        : DictionaryException("Word already exists: " + word) {}
};

class FileIOException : public DictionaryException {
public:
    explicit FileIOException(const std::string& path)
        : DictionaryException("File error: " + path) {}
};
