#ifndef GAME_H
#define GAME_H

char **init_circuit(void);
void game_loop(char **circuit);
void free_circuit(char **circuit);
void render_circuit(char **circuit);

#endif