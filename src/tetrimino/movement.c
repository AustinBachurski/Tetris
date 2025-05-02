#include "movement.h"

#include "gamesettings.h"
#include "moveleft.h"
#include "moveright.h"
#include "../game/game.h"
#include "../tetrimino/tetrimino.h"

static void indices_for_light_blue(Tetrimino const *tetrimino, int indices[]);
static void indices_for_dark_blue(Tetrimino const *tetrimino, int indices[]);
static void indices_for_orange(Tetrimino const *tetrimino, int indices[]);
static void indices_for_yellow(Tetrimino const *tetrimino, int indices[]);
static void indices_for_green(Tetrimino const *tetrimino, int indices[]);
static void indices_for_red(Tetrimino const *tetrimino, int indices[]);
static void indices_for_magenta(Tetrimino const *tetrimino, int indices[]);
static void rotate_tetrimino(Tetrimino *tetrimino);

void move_tetrimino(GameData *game, char const direction)
{
    switch (direction)
    {
        // Left
        case 'r':
            move_tetrimino_left(game);
            break;

        // Right
        case 't':
            move_tetrimino_right(game);
            break;

        // Rotate
        case 'f':
            return;

        // Down
        case 's':
            return;
    }
}

static void indices_for(Tetrimino const *tetrimino, int indices[])
{
    switch (tetrimino->type)
    {
        case Tetrimino_empty:
            return;

        case Tetrimino_lightBlue:
            indices_for_light_blue(tetrimino, indices);
            return;

        case Tetrimino_darkBlue:
            indices_for_dark_blue(tetrimino, indices);
            return;

        case Tetrimino_orange:
            indices_for_orange(tetrimino, indices);
            return;

        case Tetrimino_yellow:
            indices_for_yellow(tetrimino, indices);
            return;

        case Tetrimino_green:
            indices_for_green(tetrimino, indices);
            return;

        case Tetrimino_red:
            indices_for_red(tetrimino, indices);
            return;

        case Tetrimino_magenta:
            indices_for_magenta(tetrimino, indices);
            return;
    }
}

static void indices_for_light_blue(Tetrimino const *tetrimino, int indices[])
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

static void indices_for_dark_blue(Tetrimino const *tetrimino, int indices[])
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

static void indices_for_orange(Tetrimino const *tetrimino, int indices[])
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

static void indices_for_yellow(Tetrimino const *tetrimino, int indices[])
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

static void indices_for_green(Tetrimino const *tetrimino, int indices[])
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

static void indices_for_red(Tetrimino const *tetrimino, int indices[])
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

static void indices_for_magenta(Tetrimino const *tetrimino, int indices[])
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

static void rotate_tetrimino(Tetrimino *tetrimino)
{
    switch (tetrimino->orientation)
    {
        case North:
            tetrimino->orientation = East;
            return;

        case East:
            tetrimino->orientation = South;
            return;

        case South:
            tetrimino->orientation = West;
            return;

        case West:
            tetrimino->orientation = North;
            return;
    }
}

