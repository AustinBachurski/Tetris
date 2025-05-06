#include "movement.h"

#include "gamesettings.h"
#include "movedown.h"
#include "tetrimino.h"
#include "../game/game.h"

#include <stdatomic.h>

static void indices_for_light_blue(Tetrimino const *tetrimino, int indices[]);
static void indices_for_dark_blue(Tetrimino const *tetrimino, int indices[]);
static void indices_for_orange(Tetrimino const *tetrimino, int indices[]);
static void indices_for_yellow(Tetrimino const *tetrimino, int indices[]);
static void indices_for_green(Tetrimino const *tetrimino, int indices[]);
static void indices_for_red(Tetrimino const *tetrimino, int indices[]);
static void indices_for_magenta(Tetrimino const *tetrimino, int indices[]);
static void rotate_tetrimino(Tetrimino *tetrimino);
static void validate_and_move(GameData *game, Command const command);

void apply_changes(GameData *game, MovementData const *data)
{
    // Clear old spaces.
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        game->playfield[data->sourceIndices[i]] = Tetrimino_empty;
    }

    // Assign new spaces.
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        game->playfield[data->targetIndices[i]] = game->currentTetrimino.type;
    }

    game->currentTetrimino = data->target;
}

bool is_self(int const target, int const sourceIndices[])
{
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        if (sourceIndices[i] == target)
        {
            return true;
        }
    }

    return false;
}

void move_tetrimino(GameData *game, atomic_int *command)
{
    Command inputCommand = (Command)atomic_load_explicit(command,
                                                         memory_order_acquire);
    if (!inputCommand)
    {
        return;
    }

    validate_and_move(game, inputCommand);

    atomic_store_explicit(command,
                          (int)Command_doNothing,
                          memory_order_release);
}

void indices_for(Tetrimino const *tetrimino, int indices[])
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
            indices[2] = tetrimino->centroid - PLAYFIELD_COLUMNS;
            indices[3] = tetrimino->centroid - PLAYFIELD_COLUMNS + 1;
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
            indices[2] = tetrimino->centroid - PLAYFIELD_COLUMNS;
            indices[3] = tetrimino->centroid - PLAYFIELD_COLUMNS + 1;
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
            indices[2] = tetrimino->centroid - PLAYFIELD_COLUMNS;
            indices[3] = tetrimino->centroid - PLAYFIELD_COLUMNS - 1;
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

static void validate_and_move(GameData *game, Command const command)
{
    switch (command)
    {
        case Command_doNothing:
            [[fallthrough]];
        case Command_playAgain:
            [[fallthrough]];
        case Command_quit:
            return;

        case Command_moveLeft:
            return;

        case Command_moveRight:
            return;

        case Command_moveDown:
            move_tetrimino_down(game);
            return;

        case Command_rotate:
            rotate_tetrimino(&game->currentTetrimino);
            return;
    }
}
