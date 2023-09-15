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
    bool debug;
};

struct Game *init_game(size_t height, size_t width, bool DEBUG);
char **init_circuit(void);
void debug_mode(struct Game *game);
void game_loop(struct Game *game);
void free_circuit(char **circuit);
void render_circuit(struct Game *game);

void free_game(struct Game *game);

#endif