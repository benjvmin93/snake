#include "food.h"
#include "memory.h"


struct Food *init_food(size_t max_x, size_t max_y)
{
    struct Food *food = xmalloc(sizeof(struct Food));
    food->x = (rand() % max_x) + 1;
    food->y = (rand() % max_y) + 1;

    return food;
}

void free_food(struct Food *food)
{
    free(food);
}