#include "gamerunner.h"

int rungame(void)
{
    GameUI ui;
    initialize_ui(&ui);

    GameElements game;

    Tetrimino current = make_random_tetrimino(bag);
    Tetrimino next = make_random_tetrimino(bag);

    spawn_tetrimino(&current);
    show_preview(&next);

    return 0;
}

