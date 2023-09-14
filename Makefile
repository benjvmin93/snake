CC = gcc

CFLAGS=-Wextra -Wall
FILES = main.c game.c memory.c snake.c food.c

LIBS=-lncurses

all:
	${CC} ${CFLAGS} -o main ${FILES} ${LIBS}

debug:
	${CC} ${CFLAGS} -fsanitize=address -g -o main ${FILES} ${LIBS}

clean:
	rm -f main