#include <math.h>

#define MILLION 1000000
#define WIDTH 480
#define HEIGHT 320
#define SENSITIVITY_SCALE 5

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "font_types.h"
#include "mzapo_parlcd.h"
#include "mzapo_regs.h"
#include "drawing.h"
#include "utils.h"
#include "game.h"
#include "game_objects.h"
#include "checker_game.h"
#include "draw_game.h"
#include "game_logic.h"

extern unsigned short *fb;
extern int diffNum;

int create_round(unsigned char *mem_base, unsigned char *parlcd_mem_base, struct timespec loop_delay, int number_round, int *num_win_round_blue, int *num_win_round_red) {
    int r = *(volatile uint32_t *) (mem_base + SPILED_REG_KNOBS_8BIT_o);
    if ((r & 0x2000000) != 0) {
        return 1;
    }
    struct game_data data[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data[i][j].x_pos = 160 * j + 80;
            data[i][j].y_pos = 107 * i + 53;
            data[i][j].figure = -1;
            data[i][j].active = false;
        }
    }
    bool player_1 = true;  // X if true, O if false
    bool new_figure = true;
    int knob_pos; // blue knob
    reset_line(mem_base);
    if(diffNum == 0) {
        printf("1 player mode\n");
    }
    else if(diffNum == 1) {
        printf("2 player mode\n");
    }
    draw_board_background();
    draw_board();

    // Redraw the frame buffer to reflect changes
    write_frame_buffer(parlcd_mem_base);
    int knob_pos_before = 0;
    struct timespec move_delay;
    move_delay.tv_sec = 0;
    move_delay.tv_nsec = 500 * MILLION; // 500 milliseconds

    uint32_t lcd_value = 4294967295;  // Initialize LCD timer value

    while (true) {
        int r = *(volatile uint32_t *) (mem_base + SPILED_REG_KNOBS_8BIT_o);
        if ((r & 0x2000000) != 0) {
            return 1;
        }

        // Update the timer for the current player move
        lcd_line(&lcd_value, mem_base);

        // Player's move
        if ((r & 0x4000000) != 0 && player_1) {
            save_move(data, player_1);
            if (check_win(data, num_win_round_blue, num_win_round_red)) {
                return 0;
            }
            if (check_draw(data)) {
                printf("Round ended with draw\n");
                return 0;
            }
            player_1 = false;
            clock_nanosleep(CLOCK_MONOTONIC, 0, &move_delay, NULL); // Delay after player's move
            new_figure = true;
        } else if ((r & 0x3000000) != 0 && !player_1 && diffNum == 1) {
            save_move(data, player_1);
            if (check_win(data, num_win_round_blue, num_win_round_red)) {
                return 0;
            }
            if (check_draw(data)) {
                printf("Round ended with draw\n");
                return 0;
            }
            player_1 = true;
            clock_nanosleep(CLOCK_MONOTONIC, 0, &move_delay, NULL); // Delay after player's move
            new_figure = true;
        }

        // Computer's move (Player 2)
        if (diffNum == 0 && !player_1) {
            computers_move(data);
            draw_board_background();
            draw_board();
            draw_figures(data);
            write_frame_buffer(parlcd_mem_base); // Update the display
            if (check_win(data, num_win_round_blue, num_win_round_red)) {
                return 0;
            }
            if (check_draw(data)) {
                printf("Round ended with draw\n");
                return 0;
            }
            player_1 = true;
            clock_nanosleep(CLOCK_MONOTONIC, 0, &move_delay, NULL); // Delay after computer's move
            new_figure = true;
        }

        if (new_figure) {
            printf("new figure\n");
            create_figure(data, player_1);
            new_figure = false;
        }

        if (player_1) {
            knob_pos = (((r >> 16) & 0xff) / SENSITIVITY_SCALE) * 320 / 256;
        } else {
            knob_pos = (((r & 0xff) / SENSITIVITY_SCALE) * 480) / 256;
        }
        draw_board_background();
        draw_board();
        if (knob_pos != knob_pos_before) {
            get_move(mem_base, data, player_1, knob_pos_before, knob_pos);
        }
        
        draw_figures(data);
        
        parlcd_write_cmd(parlcd_mem_base, 0x2c);
        for (int ptr = 0; ptr < WIDTH * HEIGHT; ptr++) {
            parlcd_write_data(parlcd_mem_base, fb[ptr]);
        }
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
        knob_pos_before = knob_pos;
    }
}

void write_frame_buffer(unsigned char *parlcd_mem_base) {
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (int ptr = 0; ptr < WIDTH * HEIGHT; ptr++) {
        parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }
}
