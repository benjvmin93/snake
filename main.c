#include <ncurses.h>
#include <string.h>

#include "game.h"


int usage(void)
{
    printf("./snake [CIRCUIT_HEIGHT] [CIRCUIT_WIDTH]");
    return EXIT_SUCCESS;
}

struct Game *prepare_game(int argc, char *argv[])
{
    size_t CIRCUIT_HEIGHT = 45;
    size_t CIRCUIT_WIDTH = 25;
    bool DEBUG = false;

    if (argc == 3)
    {
        CIRCUIT_HEIGHT = atoi(argv[1]);
        CIRCUIT_WIDTH = atoi(argv[2]);
    }

    char *env = getenv("SNAKE_ENV");
    if (env != NULL && !strcmp(env, "DEBUG"))
    {
        DEBUG = true;
    }

    struct Game *game = init_game(CIRCUIT_HEIGHT, CIRCUIT_WIDTH, DEBUG);

    return game;
}

int main(int argc, char *argv[])
{
    if (argc != 3 && argc != 1)
        usage();

    struct Game *game = prepare_game(argc, argv);

    if (!game->debug)
    {
        initscr();
        cbreak();
        noecho();
        curs_set(FALSE);
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        game_loop(game);
        curs_set(TRUE);
        echo();
        endwin();
    }
    else
    {
        debug_mode(game);
    }

    free_game(game);
    return EXIT_SUCCESS;
}
