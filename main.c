#include "game.h"
#include <ncurses.h>

int main(void)
{
	initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

	struct Game *game = init_game();
    game_loop(game);
    free_game(game);
    endwin();
    return 0;
}
