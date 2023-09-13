all:
	gcc -fsanitize=address -o main -g main.c game.c memory.c -lncurses