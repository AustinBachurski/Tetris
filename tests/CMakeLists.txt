cmake_minimum_required(VERSION 4.0)

find_package(Curses REQUIRED)

add_executable(tetris_tests)

target_compile_definitions(tetris_tests PRIVATE UNIT_TEST)

target_compile_options(tetris_tests PRIVATE
    -O0
    -g3
    -fsanitize=address
)

# Test source files.
target_sources(tetris_tests PRIVATE
    tests.c
    unity/unity.c
    movement/gravity.c
    movement/movedown.c
    movement/moveleft.c
    movement/moveright.c
    randombag/randombag.c
    placement/placement.c
    rotation/rotation.c
    utilities/utilities.c
)

target_include_directories(tetris_tests PRIVATE
    unity
    movement
    randombag
    placement
    rotation
    utilities
)

# Game source files.
target_sources(tetris_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src/game/game.c
    ${CMAKE_SOURCE_DIR}/src/game/input.c
    ${CMAKE_SOURCE_DIR}/src/ui/ui.c
    ${CMAKE_SOURCE_DIR}/src/tetrimino/movement.c
    ${CMAKE_SOURCE_DIR}/src/tetrimino/movedown.c
    ${CMAKE_SOURCE_DIR}/src/tetrimino/moveleft.c
    ${CMAKE_SOURCE_DIR}/src/tetrimino/moveright.c
    ${CMAKE_SOURCE_DIR}/src/tetrimino/rotation.c
)

target_include_directories(tetris_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src/game
    ${CMAKE_SOURCE_DIR}/src/tetrimino
    ${CMAKE_SOURCE_DIR}/src/ui
)

target_link_options(tetris_tests PRIVATE -fsanitize=address)
target_link_libraries(tetris_tests PRIVATE ${CURSES_LIBRARIES})

add_test("Tetris Unit Tests" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tetris_tests)

