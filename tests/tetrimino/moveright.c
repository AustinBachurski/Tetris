#include "moveright.h"

#include "../../src/game/game.h"
#include "../../src/game/gamesettings.h"
#include "../../src/tetrimino/moveright.h"

#include "../utilities/utilities.h"
#include "../unity/unity.h"

extern void clear_playfield(GameData *game);
extern void spawn_tetrimino(GameData *game);

static int lightBlueMovedIndices[SQUARES_PER_TETRIMINO] = { 4, 5, 6, 7, };
/*
static int darkBlueMovedIndices[SQUARES_PER_TETRIMINO] = { 13, 23, 24, 25, };
static int orangeMovedIndices[SQUARES_PER_TETRIMINO] = { 15, 23, 24, 25, };
static int yellowMovedIndices[SQUARES_PER_TETRIMINO] = { 14, 15, 24, 25 };
static int greenMovedIndices[SQUARES_PER_TETRIMINO] = { 14, 15, 23, 24 };
static int redMovedIndices[SQUARES_PER_TETRIMINO] = { 13, 14, 24, 25 };
static int magentaMovedIndices[SQUARES_PER_TETRIMINO] = { 14, 23, 24, 25 };

static char const *openSucceed = "Space is open, move should succeed.";
static char const *hitBottom = "Bottom of playfield, move should fail.";
static char const *newDrop = "New drop, move should succeed.";
static char const *occupiedSpace = "Space is now occupied, move_down should fail.";
*/
static char const *incorrectLocation = "Tetrimino was not in correct location.";

void move_light_blue_tetrimino_right(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_lightBlue, Facing_up };
    spawn_tetrimino(&game);

    TEST_ASSERT_MESSAGE(!correct_spaces_occupied(&game, lightBlueMovedIndices),
                        "Tetrimino already at move right location prior to move.");

    move_tetrimino_right(&game);

    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, lightBlueMovedIndices),
                        incorrectLocation);
}

