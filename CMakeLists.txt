cmake_minimum_required(VERSION 3.15)
project(EnRuDictionary VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(dictionary_lib
    src/Word.cpp
    src/DictionaryEntry.cpp
    src/Dictionary.cpp
    src/DictionaryManager.cpp
)
target_include_directories(dictionary_lib PUBLIC include)

add_executable(dictionary_app src/main.cpp)
target_link_libraries(dictionary_app PRIVATE dictionary_lib)

enable_testing()
add_subdirectory(tests)
