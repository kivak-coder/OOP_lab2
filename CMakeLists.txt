cmake_minimum_required(VERSION 3.14)
project(five_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем поддержку GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9fdabf5c4cb4f1100db73d1.zip
)

# Основная библиотека
add_library(five_lib 
    src/five.cpp
)

target_include_directories(five_lib 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Основное приложение
add_executable(main main.cpp)
target_link_libraries(main five_lib)

# Тесты
add_executable(tests
    test/test_five.cpp
)

target_link_libraries(tests
    five_lib
    gtest_main
    gtest
)

target_include_directories(tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Добавляем цель для запуска тестов
include(GoogleTest)
gtest_discover_tests(tests)