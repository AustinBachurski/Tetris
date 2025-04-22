#ifndef TETRIS_GAME_RUNNER_H
#define TETRIS_GAME_RUNNER_H

#include "gamesettings.h"
#include "../ui/ui.h"
#include "../tetriminos/tetrimino.h"

typedef struct GameData
{
    GameUI ui;
    Tetrimino currentTetrimino;
    Tetrimino nextTetrimino;
    TetriminoColor randomBag[TETRIMINO_COUNT];
    TetriminoColor playfield[PLAYFIELD_SIZE];
} GameData;

void play_tetris(void);

void clear_playfield(GameData *game);
void cycle_in_next_tetrimino(GameData *game);
[[nodiscard]] bool is_game_over(GameData *game);
TetriminoColor get_next_tetrimino(TetriminoColor bag[]);
void initialize_game(GameData *game);
Tetrimino make_random_tetrimino(TetriminoColor bag[]);
TetriminoColor only_one_remains(TetriminoColor bag[]);
void place_tetrimino(GameData *game, int const indices[]);
void reset_bag(TetriminoColor bag[]);
[[nodiscard]] bool space_is_occupied(GameData* game, int const indices[]);
void spawn_tetrimino(GameData *game);
void wait_for_keypress(GameData *game);

#endif

