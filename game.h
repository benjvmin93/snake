#ifndef GAME_H
#define GAME_H

#include "snake.h"

struct Game
{
    struct Snake *snake;
    char **circuit;
};

struct Game *init_game(void);
char **init_circuit(void);
void game_loop(struct Game *game);
void free_circuit(char **circuit);
void render_circuit(char **circuit);
void free_game(struct Game *game);

#endif