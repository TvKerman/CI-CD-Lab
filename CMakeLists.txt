cmake_minimum_required(VERSION 4.0)
project(lab)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(run_tests tests/test_bigint.cpp)
target_link_libraries(run_tests gtest_main BigIntLib)

include(GoogleTest)
gtest_discover_tests(run_tests)
