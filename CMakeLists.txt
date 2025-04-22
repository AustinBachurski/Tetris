cmake_minimum_required(VERSION 4.0)

project(Tetris LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED YES)

set(CMAKE_C_FLAGS "${CMAKE_CRR_FLAGS} -Werror -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address -g3")
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

find_package(Curses REQUIRED)

add_executable(tetris src/main.c
                      src/game/game.c
                      src/tetriminos/gravity.c
                      src/ui/ui.c
)

target_include_directories(tetris PRIVATE src/game
                                          src/tetriminos
                                          src/ui
)

target_link_libraries(tetris ${CURSES_LIBRARIES})


# UNIT TESTING

add_executable(tetris_tests tests/tests.c
                            tests/unity/unity.c
                            tests/randombag/randombag.c
                            src/game/game.c
                            src/tetriminos/gravity.c
                            src/ui/ui.c
)

target_include_directories(tetris_tests PRIVATE tests/unity
                                                tests/randombag
                                                src/game
                                                src/tetriminos
                                                src/ui
)

target_link_libraries(tetris_tests ${CURSES_LIBRARIES})

