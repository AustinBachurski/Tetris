cmake_minimum_required(VERSION 4.0)

find_package(Curses REQUIRED)

add_executable(tetris)

target_compile_options(tetris PRIVATE -O3)

target_sources(tetris PRIVATE
    main.c
    game/game.c
    game/input.c
    tetrimino/movement.c
    tetrimino/movedown.c
    tetrimino/moveleft.c
    tetrimino/moveright.c
    tetrimino/rotation.c
    ui/ui.c
)

target_include_directories(tetris PRIVATE
    game
    tetrimino
    ui
)

target_link_libraries(tetris PRIVATE ${CURSES_LIBRARIES})

