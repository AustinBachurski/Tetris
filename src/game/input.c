#include "game.h"

#include <curses.h>

#include <stdatomic.h>

static void handle_input(char const input, atomic_int *command);

void read_in_user_input(atomic_int *command)
{
    while (true)
    {
        handle_input(getch(), command);
    }
}


static void handle_input(char const input, atomic_int *command)
{
    while (!atomic_load_explicit(command, memory_order_acquire))
    { }

    switch (input)
    {
        // Left
        case 'r':
            atomic_store_explicit(command,
                                  Command_moveLeft,
                                  memory_order_release);
            return;

        // Right
        case 't':
            atomic_store_explicit(command,
                                  Command_moveRight,
                                  memory_order_release);
            return;

        // Rotate
        case 'f':
            atomic_store_explicit(command,
                                  Command_rotate,
                                  memory_order_release);
            return;

        // Down
        case 's':
            atomic_store_explicit(command,
                                  Command_moveDown,
                                  memory_order_release);
            return;
    }
}
