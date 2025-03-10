
#include <stdbool.h>

#ifndef TICTACTOE_GAME_LOGIC_H
#define TICTACTOE_GAME_LOGIC_H


#include "game_objects.h"

void create_figure(struct game_data data[3][3],bool player);

int find_next_free(struct game_data data[3][3], int row, int col, int direction);

void get_move(unsigned char *mem_base, struct game_data data[3][3], bool player, int prev_pos, int current_pos);

void save_move(struct game_data data[3][3],bool player);

int minimax(struct game_data data[3][3], int depth, bool is_maximizing);

void computers_move(struct game_data data[3][3]);

#endif //TICTACTOE_GAME_LOGIC_H
