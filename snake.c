#include <ncurses.h>

#include "snake.h"
#include "memory.h"

#define INITIAL_SNAKE_SIZE 10

/*
    Initialize snake at position x, y.
    The snake's size is according to INTIAL_SNAKE_SIZE.
*/
struct Snake *init_snake(size_t x, size_t y)
{
    struct Snake *snake = xmalloc(sizeof(struct Snake));
    snake->x = x;
    snake->y = y;
    snake->next = NULL;

    struct Snake *ptr = snake;
    for(size_t i = 1; i < INITIAL_SNAKE_SIZE; ++i)
    {
        ptr->next = xmalloc(sizeof(struct Snake));
        ptr->next->x = x - i;
        ptr->next->y = y;
        ptr = ptr->next;
        ptr->next = NULL;
    }
    
    return snake;
}

void print_snake(struct Snake *snake)
{
    struct Snake *ptr = snake;

    while (ptr)
    {
        printf("x=%ld, y=%ld -->", ptr->x, ptr->y);
        ptr = ptr->next;
    }
}

void free_snake(struct Snake *snake)
{
    while (snake)
    {
        struct Snake *tmp = snake;
        snake = snake->next;
        free(tmp);
    }
}

void update_snake_pos(struct Snake *snake, int *direction)
{
    // Snake position update is about shifting all
    // the coordinates from the head to the tail of the snake.
    struct Snake *ptr = snake;

    int tmp_x = ptr->x;
    int tmp_y = ptr->y;

    while (ptr->next)
    {
        int x = ptr->next->x;
        int y = ptr->next->y;

        ptr->next->x = tmp_x;
        ptr->next->y = tmp_y;

        tmp_x = x;
        tmp_y = y;

        ptr = ptr->next;
    }

    // Then we update the coordinates of the head.

    if (*direction == KEY_UP)
        snake->y -= 1;
    if (*direction == KEY_DOWN)
        snake->y += 1;
    if (*direction == KEY_LEFT)
        snake->x -= 1;
    if (*direction == KEY_RIGHT)
        snake->x += 1;
}