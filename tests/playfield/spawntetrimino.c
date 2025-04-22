#include "spawntetrimino.h"

#include "../game/game.h"
#include "../game/gamesettings.h"
#include "../tetriminos/tetrimino.h"

#include "unity.h"

bool correct_spaces_occupied(GameData* game, int const indices[])
{
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        if (Tetrimino_empty == game->playfield[indices[i]])
        {
            return false;
        }
    }
    return true;
}

void spawn_light_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_lightBlue, Facing_up };

    TEST_ASSERT_MESSAGE(game.currentTetrimino.centroid != LIGHTBLUE_SPAWNPOINT,
                        "Light blue centroid set prior to spawn.");
    TEST_ASSERT_MESSAGE(!correct_spaces_occupied(&game, lightBlueSpawnIndices),
                        "Map spaces for light blue not empty prior to spawn.");

    spawn_tetrimino(&game);

    TEST_ASSERT_MESSAGE(game.currentTetrimino.centroid == LIGHTBLUE_SPAWNPOINT,
                        "Light blue centroid incorrect after spawn.");
    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, lightBlueSpawnIndices),
                        "Map spaces for light blue incorrect after spawn.");
}

void spawn_dark_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_darkBlue, Facing_up };

    TEST_ASSERT_MESSAGE(game.currentTetrimino.centroid != DARKBLUE_SPAWNPOINT,
                        "Dark blue centroid set prior to spawn.");
    TEST_ASSERT_MESSAGE(!correct_spaces_occupied(&game, darkBlueSpawnIndices),
                        "Map spaces for dark blue not empty prior to spawn.");

    spawn_tetrimino(&game);

    TEST_ASSERT_MESSAGE(game.currentTetrimino.centroid == DARKBLUE_SPAWNPOINT,
                        "Dark blue centroid incorrect after spawn.");
    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, darkBlueSpawnIndices),
                        "Map spaces for dark blue incorrect after spawn.");
}

void spawn_orange_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_orange, Facing_up };

    TEST_ASSERT_MESSAGE(game.currentTetrimino.centroid != ORANGE_SPAWNPOINT,
                        "Orange centroid set prior to spawn.");
    TEST_ASSERT_MESSAGE(!correct_spaces_occupied(&game, orangeSpawnIndices),
                        "Map spaces for orange not empty prior to spawn.");

    spawn_tetrimino(&game);

    TEST_ASSERT_MESSAGE(game.currentTetrimino.centroid == ORANGE_SPAWNPOINT,
                        "Orange centroid incorrect after spawn.");
    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, orangeSpawnIndices),
                        "Map spaces for orange incorrect after spawn.");
}

void spawn_yellow_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_yellow, Facing_up };

    TEST_ASSERT_MESSAGE(game.currentTetrimino.centroid != YELLOW_SPAWNPOINT,
                        "Yellow centroid set prior to spawn.");
    TEST_ASSERT_MESSAGE(!correct_spaces_occupied(&game, yellowSpawnIndices),
                        "Map spaces for yellow not empty prior to spawn.");

    spawn_tetrimino(&game);

    TEST_ASSERT_MESSAGE(game.currentTetrimino.centroid == YELLOW_SPAWNPOINT,
                        "Yellow centroid incorrect after spawn.");
    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, yellowSpawnIndices),
                        "Map spaces for yellow incorrect after spawn.");
}

void spawn_green_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_green, Facing_up };

    TEST_ASSERT_MESSAGE(game.currentTetrimino.centroid != GREEN_SPAWNPOINT,
                        "Green centroid set prior to spawn.");
    TEST_ASSERT_MESSAGE(!correct_spaces_occupied(&game, greenSpawnIndices),
                        "Map spaces for green not empty prior to spawn.");

    spawn_tetrimino(&game);

    TEST_ASSERT_MESSAGE(game.currentTetrimino.centroid == GREEN_SPAWNPOINT,
                        "Green centroid incorrect after spawn.");
    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, greenSpawnIndices),
                        "Map spaces for green incorrect after spawn.");
}

void spawn_red_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_red, Facing_up };

    TEST_ASSERT_MESSAGE(game.currentTetrimino.centroid != RED_SPAWNPOINT,
                        "Red centroid set prior to spawn.");
    TEST_ASSERT_MESSAGE(!correct_spaces_occupied(&game, redSpawnIndices),
                        "Map spaces for red not empty prior to spawn.");

    spawn_tetrimino(&game);

    TEST_ASSERT_MESSAGE(game.currentTetrimino.centroid == RED_SPAWNPOINT,
                        "Red centroid incorrect after spawn.");
    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, redSpawnIndices),
                        "Map spaces for red incorrect after spawn.");
}

void spawn_magenta_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_magenta, Facing_up };

    TEST_ASSERT_MESSAGE(game.currentTetrimino.centroid != MAGENTA_SPAWNPOINT,
                        "Magenta centroid set prior to spawn.");
    TEST_ASSERT_MESSAGE(!correct_spaces_occupied(&game, magentaSpawnIndices),
                        "Map spaces for magenta not empty prior to spawn.");

    spawn_tetrimino(&game);

    TEST_ASSERT_MESSAGE(game.currentTetrimino.centroid == MAGENTA_SPAWNPOINT,
                        "Magenta centroid incorrect after spawn.");
    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, magentaSpawnIndices),
                        "Map spaces for magenta incorrect after spawn.");
}

