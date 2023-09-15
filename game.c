#define _GNU_SOURCE
#define _POSIX_C_SOURCE 199309L

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "game.h"
#include "memory.h"
#include "snake.h"
#include "food.h"

size_t CIRCUIT_HEIGHT;
size_t CIRCUIT_WIDTH;

/*
    Initialize circuit according to CIRCUIT_WIDTH and CIRCUIT_HEIGHT.
*/
char **init_circuit(void)
{
	char **circuit = xcalloc(CIRCUIT_WIDTH, sizeof(char *));
	for (size_t i = 0; i < CIRCUIT_WIDTH; ++i)
	{
		circuit[i] = xcalloc(CIRCUIT_HEIGHT + 1, sizeof(char));
		for (size_t j = 0; j < CIRCUIT_HEIGHT + 1; ++j)
		{
			if (i == 0 || i == CIRCUIT_WIDTH - 1)
				circuit[i][j] = '-';
			else if (j == 0 || j == CIRCUIT_HEIGHT - 1)
				circuit[i][j] = '|';
            else if (j == CIRCUIT_HEIGHT)
                circuit[i][j] = '\n';
			else
				circuit[i][j] = ' ';
		}
	}
	return circuit;
}

/*
    Fill the array circuit with caracters according to the snake position.
*/
void update_circuit(struct Game *game)
{
    struct Snake *snake = game->snake;
    game->circuit[snake->y][snake->x] = 'O';
    snake = snake->next;
    while (snake != NULL)
    {
        game->circuit[snake->y][snake->x] = 'o';
        snake = snake->next;
    }
}

/*
    Initialize the game including the circuit and the snake structure.
*/
struct Game *init_game(size_t height, size_t width, bool DEBUG)
{
    CIRCUIT_HEIGHT = height;
    CIRCUIT_WIDTH = width;
    struct Game *game = xmalloc(sizeof(struct Game));
    game->start = false;
    game->circuit = init_circuit();
    game->snake = init_snake(CIRCUIT_HEIGHT / 2, CIRCUIT_WIDTH / 2, KEY_RIGHT);
    game->score = 0;
    game->speed = 1;
    game->debug = DEBUG;


    struct Snake *ptr = game->snake;

    game->circuit[ptr->y][ptr->x] = 'O';
    ptr = ptr->next;
    while (ptr != NULL)
    {
        game->circuit[ptr->y][ptr->x] = 'o';
        ptr = ptr->next;
    }

    game->food = init_food(CIRCUIT_HEIGHT, CIRCUIT_WIDTH);
    while (game->circuit[game->food->y][game->food->x] != ' ')
    {
        free_food(game->food);
        game->food = init_food(CIRCUIT_HEIGHT, CIRCUIT_WIDTH);
    }
    game->circuit[game->food->y][game->food->x] = '*';

    update_circuit(game);

    return game;
}

void render_circuit(struct Game *game)
{
    for (size_t i = 0; i < CIRCUIT_WIDTH; ++i)
	{
        for (size_t j = 0; j < CIRCUIT_HEIGHT; ++j)
        {
            mvaddch(i, j, game->circuit[i][j]);
        }
    }

    printw("\nScore: %d\n", game->score);
    printw("Game speed: x%d", game->speed);

    refresh();
}

void DEBUG_print_circuit(struct Game *game)
{
    system("@cls||clear");
    char **circuit = game->circuit;
    for (size_t i = 0; i < CIRCUIT_WIDTH; ++i)
	{
        for (size_t j = 0; j < CIRCUIT_HEIGHT; ++j)
        {
            printf("%c", circuit[i][j]);
        }
        printf("\n");
    }

    printf("Score : %d\n", game->score);
    printf("Speed : %d\n", game->speed);
    printf("Head position : %ld, %ld\n", game->snake->x, game->snake->y);
    printf("Food position : %ld, %ld\n", game->food->x, game->food->y);
}

void update_position(struct Game *game, int *direction)
{
    struct Snake *snake = game->snake;

    // Fill the old snake position with space caracter in the circuit.
    struct Snake *ptr = snake;
    while (ptr)
    {
        game->circuit[ptr->y][ptr->x] = ' ';
        ptr = ptr->next;
    }

    update_snake_pos(snake, direction);

    // Check whether the position update has reached circuir boundaries.
    ptr = snake;

    while (ptr)
    {
        if (ptr->x < 1)
            ptr->x = CIRCUIT_HEIGHT - 2;
        if (ptr->x >= CIRCUIT_HEIGHT - 1)
            ptr->x = 1;
        if (ptr->y < 1)
            ptr->y = CIRCUIT_WIDTH - 2;
        if (ptr->y >= CIRCUIT_WIDTH - 1)
            ptr->y = 1;
        
        ptr = ptr->next;
    }

    // Update circuit array according to the snake coordinates.
    update_circuit(game);
}

void free_game(struct Game *game)
{
    free_snake(game->snake);
    free_circuit(game->circuit);
    free_food(game->food);
    free(game);
}

void free_circuit(char **circuit)
{
	for (size_t i = 0; i < CIRCUIT_WIDTH; ++i)
	{
		free(circuit[i]);
	}
	free(circuit);
}

/*
    Check for debug_mode.
*/
bool isValidDBGMove(char move, int *direction)
{
    if (move != 'z' && move != 's' && move != 'q' && move != 'd')
        return false;

    if (move == 'z' && *direction == KEY_DOWN)
        return false;
    if (move == 's' && *direction == KEY_UP)
        return false;
    if (move == 'q' && *direction == KEY_RIGHT)
        return false;
    if (move == 'd' && *direction == KEY_LEFT)
        return false;

    return true;
}

/*
    Check whether the move is a arrow keybind and if it's not at the opposite of the direction.
*/
bool isValidMove(int move, int *direction)
{
    if (move != KEY_UP && move != KEY_DOWN && move != KEY_LEFT && move != KEY_RIGHT)
        return false;

    if (move == KEY_UP && *direction == KEY_DOWN)
        return false;
    if (move == KEY_DOWN && *direction == KEY_UP)
        return false;
    if (move == KEY_LEFT && *direction == KEY_RIGHT)
        return false;
    if (move == KEY_RIGHT && *direction == KEY_LEFT)
        return false;

    return true;
}

bool check_food_coord(char **circuit, size_t food_x, size_t food_y)
{
    if (circuit[food_y][food_x] != ' ')
        return false;
    return true;
}

bool check_collision(struct Game *game, size_t tail_x, size_t tail_y)
{
    // Check if snake has eat.
    if (game->snake->x == game->food->x &&
        game->snake->y == game->food->y)
        {
            grow_snake(game->snake, tail_x, tail_y);
            size_t food_x = (rand() % CIRCUIT_HEIGHT);
            size_t food_y = (rand() % CIRCUIT_WIDTH);
            while (! check_food_coord(game->circuit, food_x, food_y))
            {
                food_x = (rand() % CIRCUIT_HEIGHT) + 1;
                food_y = (rand() % CIRCUIT_WIDTH) + 1;
            }
            game->food->x = food_x;
            game->food->y = food_y;
            game->circuit[game->food->y][game->food->x] = '*';
            game->score += 10; // Increase score
            game->speed += 1; // Increase game speed for more fun
            return true;
        }

    size_t head_x = game->snake->x;
    size_t head_y = game->snake->y;

    struct Snake *ptr = game->snake->next;

    while (ptr)
    {
        if (head_x == ptr->x && head_y == ptr->y)
        {
            return false;
        }
        ptr = ptr->next;
    }
    return true;
}

void game_sleep(struct Game *game)
{
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 999999999;

    if (game->speed > 1)
        ts.tv_nsec /= game->speed;
    
    if (nanosleep(&ts, NULL) != 0)
        err(errno, "Nanosleep failed\n%ld", ts.tv_nsec);
}

void debug_mode(struct Game *game)
{
    game->start = true;
    update_circuit(game);
    DEBUG_print_circuit(game);
    int *direction = xmalloc(sizeof(int));
    *direction = KEY_RIGHT;
    char move;

    while (scanf("%c", &move) >= 0)
    {
        
        if (game->start == false)
            continue;
        
        if (move == '\n')
            continue;
        if (isValidDBGMove(move, direction))
        {
            if (move == 'z')
                *direction = KEY_UP;
            if (move == 'd')
                *direction = KEY_RIGHT;
            if (move == 'q')
                *direction = KEY_LEFT;
            if (move == 's')
                *direction = KEY_DOWN;
        }

        struct Snake *tail = get_snake_tail(game->snake);
        size_t tail_x = tail->x;
        size_t tail_y = tail->y;

        // Update the position according to the direction.
        update_position(game, direction);

        if (! check_collision(game, tail_x, tail_y))
        {
            game->start = false;
            printf("\nEnd game.\n");
            continue;
        }
        DEBUG_print_circuit(game);
    }
}

void game_loop(struct Game *game)
{
    game->start = true;
    int *direction = xmalloc(sizeof(int));
    *direction = KEY_RIGHT;
    int move;
    while ((move = getch()) != 'q')
    {
        if (game->start == false)
            continue;
        // Check whether it's a valid move
        // and update *direction in consequence.
        if (isValidMove(move, direction))
            *direction = move;
        
        // Keep track of the tail coordinates in case
        // the snake is growing.
        struct Snake *tail = get_snake_tail(game->snake);
        size_t tail_x = tail->x;
        size_t tail_y = tail->y;

        // Update the position according to the direction.
        update_position(game, direction);
        // Check for collision
        if (! check_collision(game, tail_x, tail_y))
        {   
            game->start = false;
            printw("\nYou lost\nPress q to exit");
            continue;
        }
        //Finally render circuit.
        render_circuit(game);
        game_sleep(game);
    }
    free(direction);

    render_circuit(game);
}