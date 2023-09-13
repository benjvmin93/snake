#include "game.h"
#include <ncurses.h>

/*
int main(void)
{
	char **circuit = init_circuit();
	start_game(circuit);
	free_circuit(circuit);
	return 1;
}*/

int main(void)
{
	initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    // Add your game logic here
	char **circuit = init_circuit();
	game_loop(circuit);
	free_circuit(circuit);
    // Clean up and exit
    endwin();
    return 0;
}
