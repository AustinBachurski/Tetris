#include "game.h"

#include <curses.h>

#include <stdatomic.h>

static void handle_input(char const input, atomic_int *command);

void * read_user_input(void *command)
{
    while (true)
    {
        handle_input((char)getch(), (atomic_int *)command);
    }
}

static void handle_input(char const input, atomic_int *command)
{
    while (atomic_load_explicit(command, memory_order_acquire))
    { }

    switch (input)
    {
        // Left
        case 'r':
            atomic_store_explicit(command,
                                  (int)Command_moveLeft,
                                  memory_order_release);
            return;

        // Right
        case 't':
            atomic_store_explicit(command,
                                  (int)Command_moveRight,
                                  memory_order_release);
            return;

        // Rotate
        case 'f':
            atomic_store_explicit(command,
                                  (int)Command_rotate,
                                  memory_order_release);
            return;

        // Down
        case 's':
            atomic_store_explicit(command,
                                  (int)Command_moveDown,
                                  memory_order_release);
            return;

        // Play Again
        case 'y':
            atomic_store_explicit(command,
                                  (int)Command_playAgain,
                                  memory_order_release);
            return;

        // Quit
        case 'n':
            atomic_store_explicit(command,
                                  (int)Command_quit,
                                  memory_order_release);
            return;
    }
}

