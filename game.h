#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "snake.h"

struct Game
{
    bool start;
    struct Snake *snake;
    char **circuit;
    struct Food *food;
    int score;
};

struct Game *init_game(void);
char **init_circuit(void);
void game_loop(struct Game *game);
void free_circuit(char **circuit);
void render_circuit(struct Game *game);

void free_game(struct Game *game);

#endif