#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>

struct Snake
{
    size_t x;
    size_t y;
    struct Snake *next;
    int direction;
};

struct Snake *init_snake(size_t x, size_t y, int direction);
void free_snake(struct Snake *snake);
void update_snake_pos(struct Snake *snake, int *direction);
void print_snake(struct Snake *snake);
struct Snake *get_snake_tail(struct Snake *snake);
void grow_snake(struct Snake *snake, size_t tail_x, size_t tail_y);

#endif