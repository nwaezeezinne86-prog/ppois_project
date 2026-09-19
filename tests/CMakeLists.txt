find_package(GTest REQUIRED)

add_executable(dictionary_tests
    test_word.cpp
    test_dictionary.cpp
    test_manager.cpp
)
target_link_libraries(dictionary_tests PRIVATE
    dictionary_lib
    GTest::gtest
    GTest::gtest_main
    pthread
)
include(GoogleTest)
gtest_discover_tests(dictionary_tests)
