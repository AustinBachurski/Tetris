#include "movement.h"

#include "moveleft.h"
#include "moveright.h"
#include "../game/game.h"

void move_tetrimino(GameData *game, char const direction)
{
    switch (direction)
    {
        case 'r':
            move_tetrimino_left(game);
            break;

        case 't':
            move_tetrimino_right(game);
            break;

        case 's':
            return;

        // TODO: Rotate clockwise.
        // TODO: Rotate counter clockwise.
        // TODO: Move down.
    }
}

