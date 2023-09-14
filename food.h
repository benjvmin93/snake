#include <stddef.h>

struct Food
{
    size_t x;
    size_t y;
};

struct Food *init_food(size_t max_x, size_t max_y);
void free_food(struct Food *food);