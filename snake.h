#ifndef SNAKE_H
#define SNAKE_H


#include <stdlib.h>

struct Snake
{
    size_t x;
    size_t y;
    struct Snake *next;
};

struct Snake *init_snake(size_t x, size_t y);
void free_snake(struct Snake *snake);
void update_snake_pos(struct Snake *snake, int *direction);
void print_snake(struct Snake *snake);

#endif