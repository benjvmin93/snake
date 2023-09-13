#define _GNU_SOURCE

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "game.h"
#include "memory.h"

#define CIRCUIT_SIZE 30

char **init_circuit(void)
{
	char **circuit = xcalloc(CIRCUIT_SIZE, sizeof(char *));
	for (size_t i = 0; i < CIRCUIT_SIZE; ++i)
	{
		circuit[i] = xcalloc(CIRCUIT_SIZE + 1, sizeof(char));
		for (size_t j = 0; j < CIRCUIT_SIZE + 1; ++j)
		{
			if (i == 0 || i == CIRCUIT_SIZE - 1)
				circuit[i][j] = '-';
			else if (j == 0 || j == CIRCUIT_SIZE - 1)
				circuit[i][j] = '|';
            else if (j == CIRCUIT_SIZE)
                circuit[i][j] = '\n';
			else
				circuit[i][j] = ' ';
		}
	}
	return circuit;
}

void render_circuit(char **circuit)
{
    for (size_t i = 0; i < CIRCUIT_SIZE; ++i)
	{
        for (size_t j = 0; j < CIRCUIT_SIZE + 1; ++j)
        {
            mvaddch(i, j, circuit[i][j]);
        }
    }
    refresh();
}

bool isValidMove(size_t pos_x, size_t pos_y)
{
    if (pos_x > 0 && pos_x < CIRCUIT_SIZE &&
        pos_y > 0 && pos_y < CIRCUIT_SIZE - 1)
    {
        return true;
    }
    return false;
}

void update_position(char **circuit, size_t pos_x, size_t pos_y, int move)
{
    size_t new_pos_x = pos_x;
    size_t new_pos_y = pos_y;

    switch(move)
        {
            case KEY_UP:
            {
                if (isValidMove(pos_x, pos_y - 1))
                {
                    new_pos_x = pos_x;
                    new_pos_y = pos_y - 1;
                }
                printw("UP");
                break;
            }
            case KEY_DOWN:
            {
                if (isValidMove(pos_x, pos_y + 1))
                {
                    new_pos_x = pos_x;
                    new_pos_y = pos_y + 1;
                }
                printw("DOWN");
                break;
            }
            case KEY_LEFT:
            {
                if (isValidMove(pos_x - 1, pos_y))
                {
                    new_pos_y = pos_y;
                    new_pos_x = pos_x - 1;
                }
                printw("LEFT");

                break;
            }
            case KEY_RIGHT:
            {
                if (isValidMove(pos_x + 1, pos_y))
                {
                    new_pos_y = pos_y;
                    new_pos_x = pos_x + 1;
                }
                printw("RIGHT");

                break;
            }
            default:
                break;
        }
        circuit[pos_y][pos_x] = ' ';
        circuit[new_pos_y][new_pos_x] = 's';
}

void free_circuit(char **circuit)
{
	for (size_t i = 0; i < CIRCUIT_SIZE; ++i)
	{
		free(circuit[i]);
	}
	free(circuit);
}

WINDOW *create_window(size_t height, size_t width, size_t start_x, size_t start_y)
{
    return newwin(height, width, start_y, start_x);
}

void game_loop(char **circuit)
{
    size_t pos_x = (CIRCUIT_SIZE + 1) / 2;
    size_t pos_y = CIRCUIT_SIZE / 2;

    WINDOW *win = create_window(CIRCUIT_SIZE, CIRCUIT_SIZE, pos_x, pos_y);

    circuit[pos_y][pos_x] = 's';

    render_circuit(circuit);
    int move;
    while ((move = getch()) != 'q')
    {
        
        update_position(circuit, pos_x, pos_y, move);
        render_circuit(circuit);
    }
}

// UP: "^[[A"
// DOWN: "^[[B"
// LEFT: "^[[D"
// RIGHT: "^[[C"