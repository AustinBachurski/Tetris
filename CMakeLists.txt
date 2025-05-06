cmake_minimum_required(VERSION 4.0)

project(Tetris LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED YES)

set(CMAKE_C_FLAGS "${CMAKE_CRR_FLAGS} -Werror -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address -g3")
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

find_package(Curses REQUIRED)

add_executable(tetris src/main.c
                      src/game/game.c
                      src/game/input.c
                      src/tetrimino/movement.c
                      src/tetrimino/movedown.c
                      src/tetrimino/moveleft.c
                      src/tetrimino/moveright.c
                      src/tetrimino/rotation.c
                      src/ui/ui.c
)

target_include_directories(tetris PRIVATE src/game
                                          src/tetrimino
                                          src/ui
)

target_link_libraries(tetris ${CURSES_LIBRARIES})


# UNIT TESTING

# add_executable(tetris_tests tests/tests.c
# tests/unity/unity.c
# tests/randombag/randombag.c
# tests/playfield/spawntetrimino.c
# tests/playfield/gameover.c
# tests/tetrimino/moveleft.c
# tests/tetrimino/moveright.c
# tests/utilities/utilities.c
# src/game/game.c
# src/ui/ui.c
# src/tetrimino/movement.c
# src/tetrimino/moveleft.c
# src/tetrimino/moveright.c
# src/tetrimino/validation.c
# )
# 
# target_compile_definitions(tetris_tests PRIVATE UNIT_TEST)
# 
# target_include_directories(tetris_tests PRIVATE tests/unity
# tests/randombag
# tests/playfield
# tests/tetrimino
# tests/utilities
# src/game
# src/tetrimino
# src/ui
# )
# 
# target_link_libraries(tetris_tests ${CURSES_LIBRARIES})
# 
