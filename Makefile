CC = gcc

CFLAGS=-Wextra -Wall
FILES = main.c game.c memory.c snake.c food.c

LIBS=-lncurses

all:
	${CC} ${CFLAGS} -o snake ${FILES} ${LIBS}

debug:
	${CC} ${CFLAGS} -fsanitize=address -g -o dbg-snake ${FILES} ${LIBS}

clean:
	rm -f snake dbg-snake