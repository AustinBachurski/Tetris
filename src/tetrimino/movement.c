#include "movement.h"

#include "gamesettings.h"
#include "moveleft.h"
#include "moveright.h"
#include "../game/game.h"
#include "../tetrimino/tetrimino.h"

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


void indices_for_light_blue(Tetrimino const *tetrimino, int indices[])
{
    switch (tetrimino->orientation)
    {
        case North:
            [[fallthrough]];
        case South:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid - 1;
            indices[2] = tetrimino->centroid + 1;
            indices[3] = tetrimino->centroid + 2;
        return;

        case East:
            [[fallthrough]];
        case West:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid + PLAYFIELD_COLUMNS;
            indices[2] = tetrimino->centroid - PLAYFIELD_COLUMNS;
            indices[3] = tetrimino->centroid - PLAYFIELD_COLUMNS * 2;
        return;
    }
}

void indices_for_dark_blue(Tetrimino const *tetrimino, int indices[])
{
    switch (tetrimino->orientation)
    {
        case North:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid - 1;
            indices[2] = tetrimino->centroid - 1 - PLAYFIELD_COLUMNS;
            indices[3] = tetrimino->centroid + 1;
            return;

 
        case East:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid + PLAYFIELD_COLUMNS;
            indices[2] = tetrimino->centroid - PLAYFIELD_COLUMNS;
            indices[3] = tetrimino->centroid - PLAYFIELD_COLUMNS + 1;
            return;

        case South:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid - 1;
            indices[2] = tetrimino->centroid + 1;
            indices[3] = tetrimino->centroid + 1 - PLAYFIELD_COLUMNS;
        return;

        case West:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid - PLAYFIELD_COLUMNS;
            indices[2] = tetrimino->centroid - PLAYFIELD_COLUMNS - 1;
            indices[3] = tetrimino->centroid + PLAYFIELD_COLUMNS;
        return;
    }
}

void indices_for_orange(Tetrimino const *tetrimino, int indices[])
{
    switch (tetrimino->orientation)
    {
        case North:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid - 1;
            indices[2] = tetrimino->centroid + 1;
            indices[3] = tetrimino->centroid + 1 - PLAYFIELD_COLUMNS;
            return;

 
        case East:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid + PLAYFIELD_COLUMNS;
            indices[2] = tetrimino->centroid + PLAYFIELD_COLUMNS + 1;
            indices[3] = tetrimino->centroid - PLAYFIELD_COLUMNS;
            return;

        case South:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid - 1;
            indices[2] = tetrimino->centroid - 1 + PLAYFIELD_COLUMNS;
            indices[3] = tetrimino->centroid + 1;
        return;

        case West:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid + PLAYFIELD_COLUMNS;
            indices[2] = tetrimino->centroid - PLAYFIELD_COLUMNS;
            indices[3] = tetrimino->centroid - PLAYFIELD_COLUMNS - 1;
        return;
    }
}

void indices_for_yellow(Tetrimino const *tetrimino, int indices[])
{
    switch (tetrimino->orientation)
    {
        case North:
            [[fallthrough]];
        case East:
            [[fallthrough]];
        case South:
            [[fallthrough]];
        case West:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid + 1;
            indices[2] = tetrimino->centroid + PLAYFIELD_COLUMNS;
            indices[3] = tetrimino->centroid + PLAYFIELD_COLUMNS + 1;
            return;
    }
}

void indices_for_green(Tetrimino const *tetrimino, int indices[])
{
    switch (tetrimino->orientation)
    {
        case North:
            [[fallthrough]];
        case South:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid - 1;
            indices[2] = tetrimino->centroid + PLAYFIELD_COLUMNS;
            indices[3] = tetrimino->centroid + PLAYFIELD_COLUMNS + 1;
            return;

 
        case East:
            [[fallthrough]];
        case West:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid - PLAYFIELD_COLUMNS;
            indices[2] = tetrimino->centroid - 1;
            indices[3] = tetrimino->centroid - 1 - PLAYFIELD_COLUMNS;
        return;
    }
}

void indices_for_red(Tetrimino const *tetrimino, int indices[])
{
    switch (tetrimino->orientation)
    {
        case North:
            [[fallthrough]];
        case South:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid + 1;
            indices[2] = tetrimino->centroid + PLAYFIELD_COLUMNS;
            indices[3] = tetrimino->centroid + PLAYFIELD_COLUMNS - 1;
            return;

 
        case East:
            [[fallthrough]];
        case West:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid - PLAYFIELD_COLUMNS;
            indices[2] = tetrimino->centroid + 1;
            indices[3] = tetrimino->centroid + 1 - PLAYFIELD_COLUMNS;
        return;
    }
}

void indices_for_magenta(Tetrimino const *tetrimino, int indices[])
{
    switch (tetrimino->orientation)
    {
        case North:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid - 1;
            indices[2] = tetrimino->centroid - PLAYFIELD_COLUMNS;
            indices[3] = tetrimino->centroid + 1;
            return;

 
        case East:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid - PLAYFIELD_COLUMNS;
            indices[2] = tetrimino->centroid + 1;
            indices[3] = tetrimino->centroid + PLAYFIELD_COLUMNS;
            return;

        case South:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid - 1;
            indices[2] = tetrimino->centroid + PLAYFIELD_COLUMNS;
            indices[3] = tetrimino->centroid + 1;
        return;

        case West:
            indices[0] = tetrimino->centroid;
            indices[1] = tetrimino->centroid + PLAYFIELD_COLUMNS;
            indices[2] = tetrimino->centroid - 1;
            indices[3] = tetrimino->centroid - PLAYFIELD_COLUMNS;
        return;
    }
}

