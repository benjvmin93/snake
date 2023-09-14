#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "snake.h"

struct Game
{
    struct Snake *snake;
    struct Food *food;
    char **circuit;
    int speed; // speed multiplier
    bool start;
    int score;
};

struct Game *init_game(void);
char **init_circuit(void);
void game_loop(struct Game *game);
void free_circuit(char **circuit);
void render_circuit(struct Game *game);

void free_game(struct Game *game);

#endif