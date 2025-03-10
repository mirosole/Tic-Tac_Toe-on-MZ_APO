#include <stdbool.h>

#ifndef TICTACTOE_CHECKER_GAME_H
#define TICTACTOE_CHECKER_GAME_H

#include "game_objects.h"

bool is_winner(const struct game_data data[3][3], int player);

int find_winner(const struct game_data data[3][3]);

bool check_win(struct game_data data[3][3], int *num_win_round_blue, int *num_win_round_red);

bool check_draw(struct game_data data[3][3]);

#endif //TICTACTOE_CHECKER_GAME_H
