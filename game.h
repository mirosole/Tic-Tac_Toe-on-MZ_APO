#include <stdbool.h>
#include <time.h>

#ifndef TICTACTOE_GAME_H
#define TICTACTOE_GAME_H


int
create_round(unsigned char *mem_base, unsigned char *parlcd_mem_base, struct timespec loop_delay, int number_round, int
*num_win_round_blue, int *num_win_round_red);

void write_frame_buffer(unsigned char *parlcd_mem_base);

#endif //TICTACTOE_GAME_H





