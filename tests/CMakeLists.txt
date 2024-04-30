cmake_minimum_required(VERSION 3.20)
project(
    panoramix-test
)

set(
    CMAKE_CXX_STANDARD 20
)
set(
    CMAKE_CXX_STANDARD_REQUIRED ON
)

add_compile_options(
    -DDEBUG
)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

enable_testing()

# Windows settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(panoramix-test
    ../src/garbage.c
    ../src/logging.c
    ../src/parsing.c
    tests.cpp
)

target_include_directories(panoramix-test PUBLIC
    ../includes/
)

target_link_libraries(panoramix-test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(panoramix-test)