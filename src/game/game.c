#include "game.h"

#include "gamesettings.h"
#include "input.h"
#include "../ui/ui.h"
#include "../tetrimino/movement.h"
#include "../tetrimino/tetrimino.h"

#include <pthread.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#ifdef UNIT_TEST
    #define INTERNAL /* as nothing for unit testing */
#else
    #define INTERNAL static
#endif

static void bulk_line_clear(GameData *game, int const indices[], int const size);
INTERNAL void clear_playfield(GameData *game);
static void check_and_clear_lines(GameData *game);
static void clear_lines(GameData *game, int const rows[], int const size);
static void cycle_in_next_tetrimino(GameData *game);
static void game_loop(GameData *game, InputHandles *input, FrameTime *times);
static TetriminoColor get_next_tetrimino(TetriminoColor bag[]);
static void initialize_game(GameData *game);
static void initialize_input(InputHandles *input);
static void initialize_time(FrameTime *times);
[[nodiscard]] INTERNAL bool is_game_over(GameData const *game);
[[nodiscard]] static bool is_time_for_gravity(GameData *game);
INTERNAL Tetrimino make_random_tetrimino(TetriminoColor bag[]);
static void new_game(GameData *game, InputHandles *input);
static TetriminoColor only_one_remains(TetriminoColor const bag[]);
static void place_tetrimino(GameData *game);
INTERNAL void reset_bag(TetriminoColor bag[]);
static bool rows_are_contiguous(int const rows[], int const size);
[[nodiscard]] static bool should_be_cleared(int const rowIndex,
                                            TetriminoColor const playfield[]);
static void single_line_clear(GameData *game, int const index);
static void sleep_for(FrameTime *times);
[[nodiscard]] static int spawnpoint_for(TetriminoColor const color);
static float time_ratio(int const level);
static void update_score(GameData *game, int const lines);
static void wait_for_keypress(GameData *game);

void play_tetris(void)
{
    GameData game;
    InputHandles input;
    FrameTime times;

    initialize_game(&game);
    initialize_input(&input);
    initialize_time(&times);

    game_loop(&game, &input, &times);

    exit_game(0);
}

static void bulk_line_clear(GameData *game, int const lines[], int const size)
{
    int const sourceIndex = lines[size - 1] + PLAYFIELD_COLUMNS;

    TetriminoColor *const dest = &game->playfield[lines[0]];
    TetriminoColor *const source = &game->playfield[sourceIndex];

    memmove(dest,
            source,
            (unsigned int)
            (PLAYFIELD_SIZE - sourceIndex) * sizeof(TetriminoColor));

    memset(&game->playfield[PLAYFIELD_SIZE - (PLAYFIELD_COLUMNS * size)],
           (char)Tetrimino_empty,
           (unsigned long)(PLAYFIELD_COLUMNS * size) * sizeof(TetriminoColor));
}

INTERNAL void clear_playfield(GameData *game)
{
    memset(game->playfield, 0, PLAYFIELD_SIZE * sizeof(TetriminoColor));
}

static void check_and_clear_lines(GameData *game)
{
    int index = 0;
    int rowsIndicesToClear[SQUARES_PER_TETRIMINO];
    int linesToClear = 0;

    for (int rowBase = 0; rowBase < PLAYFIELD_ROWS; ++rowBase)
    {
        index = rowBase * PLAYFIELD_COLUMNS;
        if (should_be_cleared(index, game->playfield))
        {
            rowsIndicesToClear[linesToClear++] = index;
        }
    }

    if (!linesToClear)
    {
        return;
    }

    update_score(game, linesToClear);
    clear_lines(game, rowsIndicesToClear, linesToClear);
    animate_lines(game, rowsIndicesToClear, linesToClear);

    // Framerate limit sleep occurs before the next redraw.  At times,
    // the clear animation would appear to hang at the last step until
    // the sleep returned and playfield was redrawn. Redrawing immediately
    // after the line clear animation prevents this.
    update_screen(game);
}

static void clear_lines(GameData *game, int const rows[], int const size)
{
    if (size > 1 && rows_are_contiguous(rows, size))
    {
        bulk_line_clear(game, rows, size);
    }
    else
    {
        for (int i = size - 1; i >= 0; --i)
        {
            single_line_clear(game, rows[i]);
        }
    }
}

static void cycle_in_next_tetrimino(GameData *game)
{
    game->currentTetrimino = game->nextTetrimino;
    game->nextTetrimino = make_random_tetrimino(game->randomBag);
    place_tetrimino(game);
    set_preview(game);
    gettimeofday(&game->dropTime, NULL);
}

static void game_loop(GameData *game, InputHandles *input, FrameTime *times)
{
    while (true)
    {
        update_screen(game);
        move_tetrimino(game, &input->command);

        if (is_time_for_gravity(game))
        {
            if (!gravity_down(game))
            {
                check_and_clear_lines(game);

                if (!is_game_over(game))
                {
                    cycle_in_next_tetrimino(game);
                }
                else 
                {
                    cycle_in_next_tetrimino(game);
                    update_screen(game);

                    if (play_again(game, input))
                    {
                        new_game(game, input);
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        sleep_for(times);
    }

    pthread_cancel(input->thread);
    pthread_join(input->thread, NULL);
}

static TetriminoColor get_next_tetrimino(TetriminoColor bag[])
{
    TetriminoColor selection = only_one_remains(bag);

    if (Tetrimino_empty != selection)
    {
        reset_bag(bag);
        return selection;
    }

    int index = rand() % (TETRIMINO_COUNT - 1);

    while (Tetrimino_empty == bag[index])
    {
        index = rand() % (TETRIMINO_COUNT - 1);
    }

    selection = bag[index];
    bag[index] = Tetrimino_empty;

    return selection;
}

static void initialize_game(GameData *game)
{
    srand((unsigned int)time(NULL));
    reset_bag(game->randomBag);
    game->nextTetrimino = make_random_tetrimino(game->randomBag);
    game->level = 0;
    game->lines = 0;
    game->score = 0;

    clear_playfield(game);
    initialize_ui(game);
    set_preview(game);
    wait_for_keypress(game);
    cycle_in_next_tetrimino(game);
}

static void initialize_input(InputHandles *input)
{
    atomic_init(&input->command, (int)Command_doNothing);
    pthread_create(&input->thread, NULL, read_user_input, &input->command);
}

static void initialize_time(FrameTime *times)
{
    times->loopStart.tv_sec = 0;
    times->loopStart.tv_usec = 0;
    times->loopEnd.tv_sec = 0;
    times->loopEnd.tv_usec = 0;
    times->delta.tv_sec = 0;
    times->delta.tv_nsec = 0;
}

INTERNAL bool is_game_over(GameData const *game)
{
    int indices[SQUARES_PER_TETRIMINO];
    indices_for(&game->nextTetrimino, indices);

    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        if (Tetrimino_empty != game->playfield[indices[i]])
        {
            return true;
        }
    }
    return false;
}

static bool is_time_for_gravity(GameData *game)
{
    struct timeval now;
    gettimeofday(&now, NULL);

    long deltaSeconds = now.tv_sec - game->dropTime.tv_sec;
    long deltaMicroseconds = now.tv_usec - game->dropTime.tv_usec;

    long deltaTime = deltaSeconds * MICROSECONDS_PER_SECOND + deltaMicroseconds;
    float moveTime = MICROSECONDS_PER_SECOND * time_ratio(game->level);

    if ((float)deltaTime >= moveTime)
    {
        gettimeofday(&game->dropTime, NULL);
        return true;
    }

    return false;
}

INTERNAL Tetrimino make_random_tetrimino(TetriminoColor bag[])
{
    TetriminoColor const color = get_next_tetrimino(bag);

    return (Tetrimino){ spawnpoint_for(color), color, North };
}

static void new_game(GameData *game, InputHandles *input)
{
    pthread_cancel(input->thread);
    pthread_join(input->thread, NULL);

    initialize_game(game);

    pthread_create(&input->thread, NULL, read_user_input, &input->command);
    atomic_store_explicit(&input->command,
                          (int)Command_doNothing,
                          memory_order_release);
}

static TetriminoColor only_one_remains(TetriminoColor const bag[])
{
    TetriminoColor selection = Tetrimino_empty;

    for (int i = 0; i < TETRIMINO_COUNT; ++i)
    {
        if (Tetrimino_empty != bag[i])
        {
            if (Tetrimino_empty != selection)
            {
                return Tetrimino_empty;
            }

            selection = bag[i];
        }
    }

    return selection;
}

static void place_tetrimino(GameData *game)
{
    int indices[SQUARES_PER_TETRIMINO];
    indices_for(&game->currentTetrimino, indices);

    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        game->playfield[indices[i]] = game->currentTetrimino.type;
    }
}

INTERNAL void reset_bag(TetriminoColor bag[])
{
    for (int i = 0; i < TETRIMINO_COUNT; ++i)
    {
        bag[i] = (TetriminoColor)(i + 1);
    }
}

static bool rows_are_contiguous(int const rows[], int const size)
{
    int compare = rows[0];

    for (int i = 1; i < size; ++i)
    {
        if (rows[i] != (compare += PLAYFIELD_COLUMNS))
        {
            return false;
        }
    }

    return true;
}

static bool should_be_cleared(int const rowIndex,
                              TetriminoColor const playfield[])
{
    for (int column = 0; column < PLAYFIELD_COLUMNS; ++column)
    {
        if (Tetrimino_empty == playfield[rowIndex + column])
        {
            return false;
        }
    }

    return true;
}

static void single_line_clear(GameData *game, int const index)
{
    if (index != PLAYFIELD_SIZE - PLAYFIELD_COLUMNS)
    {
        memmove(&game->playfield[index],
                &game->playfield[index + PLAYFIELD_COLUMNS],
                (unsigned int) (PLAYFIELD_SIZE - PLAYFIELD_COLUMNS - index)
                    * sizeof(TetriminoColor));
    }

    memset(&game->playfield[PLAYFIELD_SIZE - PLAYFIELD_COLUMNS],
           (char)Tetrimino_empty,
           PLAYFIELD_COLUMNS * sizeof(TetriminoColor));
}

static void sleep_for(FrameTime *times)
{
    gettimeofday(&times->loopEnd, NULL);

    long frameTime = times->loopEnd.tv_usec - times->loopStart.tv_usec;

    if (frameTime < TARGET_FRAME_TIME)
    {
        times->delta.tv_nsec =
            (TARGET_FRAME_TIME - frameTime) * NANOSECONDS_PER_MICROSECOND;

        nanosleep(&times->delta, NULL);
    }

    gettimeofday(&times->loopStart, NULL);
}

static int spawnpoint_for(TetriminoColor const color)
{
    switch (color)
    {
        case Tetrimino_empty:
            // TODO: Should never happen.
            break;

        case Tetrimino_lightBlue:
            return LIGHTBLUE_SPAWNPOINT;

        case Tetrimino_darkBlue:
            return DARKBLUE_SPAWNPOINT;

        case Tetrimino_orange:
            return ORANGE_SPAWNPOINT;

        case Tetrimino_yellow:
            return YELLOW_SPAWNPOINT;

        case Tetrimino_green:
            return GREEN_SPAWNPOINT;

        case Tetrimino_red:
            return RED_SPAWNPOINT;

        case Tetrimino_magenta:
            return MAGENTA_SPAWNPOINT;
    }

    return -1;
}

static float time_ratio(int const level)
{
    switch (level)
    {
        case 0:
            return .7987f;

        case 1:
            return .7155f;

        case 2:
            return .6323f;

        case 3:
            return .5491f;

        case 4:
            return .4659f;

        case 5:
            return .3827f;

        case 6:
            return .2995f;

        case 7:
            return .2163f;

        case 8:
            return .1331f;

        case 9:
            return .09985f;

        case 10:
            [[fallthrough]];
        case 11:
            [[fallthrough]];
        case 12:
            return .0832f;

        case 13:
            [[fallthrough]];
        case 14:
            [[fallthrough]];
        case 15:
            return .06655f;

        case 16:
            [[fallthrough]];
        case 17:
            [[fallthrough]];
        case 18:
            return .0499f;

        case 19:
            [[fallthrough]];
        case 20:
            [[fallthrough]];
        case 21:
            [[fallthrough]];
        case 22:
            [[fallthrough]];
        case 23:
            [[fallthrough]];
        case 24:
            [[fallthrough]];
        case 25:
            [[fallthrough]];
        case 26:
            [[fallthrough]];
        case 27:
            [[fallthrough]];
        case 28:
            return .0333f;
    }

    return .01665f;
}

static int calculate_score(int const base, int const level)
{
    if (level < 10)
    {
        return base + base * level;
    }
    else
{
        return base * (level + 1);
    }
}

static void update_score(GameData *game, int const linesToClear)
{
    switch(linesToClear)
    {
        case 1:
            game->score += calculate_score(40, game->level);
            break;

        case 2:
            game->score += calculate_score(100, game->level);
            break;

        case 3:
            game->score += calculate_score(300, game->level);
            break;

        case 4:
            game->score += calculate_score(1200, game->level);
            break;
    }

    game->lines += linesToClear;
    game->level = game->lines / 10 + 1;
}

static void wait_for_keypress(GameData *game)
{
    mvwprintw(game->ui.playfieldWindow, 8, 4, "Press any key");
    mvwprintw(game->ui.playfieldWindow, 9, 5, "to begin...");
    wrefresh(game->ui.playfieldWindow);
    getch();
    mvwprintw(game->ui.playfieldWindow, 8, 4, "             ");
    mvwprintw(game->ui.playfieldWindow, 9, 5, "           ");
    wrefresh(game->ui.playfieldWindow);
}

