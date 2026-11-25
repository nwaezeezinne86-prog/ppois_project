cmake_minimum_required(VERSION 3.14)
project(EnRuDictionary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT MSVC)
  add_compile_options(-Wall -Wextra -pedantic)
endif()

add_library(dictlib src/text_utils.cpp src/entry.cpp src/dictionary.cpp)
target_include_directories(dictlib PUBLIC include)

add_executable(dictionary src/main.cpp)
target_link_libraries(dictionary dictlib)

enable_testing()
add_executable(run_tests tests/test_dictionary.cpp)
target_link_libraries(run_tests dictlib)
add_test(NAME unit_tests COMMAND run_tests)
