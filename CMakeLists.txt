cmake_minimum_required(VERSION 3.20)

project(AlgorithmsAndDataStructuresCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(basic_usage
    examples/basic_usage.cpp
)

target_include_directories(basic_usage PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

enable_testing()

add_executable(test_dynamic_array
    tests/test_dynamic_array.cpp
)

target_include_directories(test_dynamic_array PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(test_dynamic_array PRIVATE
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(test_dynamic_array)