cmake_minimum_required(VERSION 4.0)

project(Tetris LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

add_compile_options(
    -Werror
    -Wall
    -Wcast-align
    -Wdouble-promotion
    -Wduplicated-branches
    -Wduplicated-cond
    -Wextra
    -Wconversion
    -Wimplicit-fallthrough
    -Wlogical-op
    -Wmisleading-indentation
    -Wnull-dereference
    -Wpedantic
    -Wshadow
    -Wsign-conversion
    -Wunused
)

add_subdirectory(src)

option(RUN_TESTS NO)

if(RUN_TESTS)
    include(CTest)
    add_subdirectory(tests)
endif()

