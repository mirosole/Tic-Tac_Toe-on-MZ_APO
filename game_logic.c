#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "game_logic.h"
#include "checker_game.h"
#include "game_objects.h"
#include "utils.h"
#include "game.h"
#include "pages.h"

void create_figure(struct game_data data[3][3],bool player) {
    for (unsigned int row = 0; row < 3; row++) {
        for (unsigned int col = 0; col < 3; col++) {
            if (data[row][col].figure == -1) {
                data[row][col].figure = player;
                data[row][col].active = true;
                return;
            }
        }
    }
}

int find_next_free(struct game_data data[3][3], int row, int col, int direction) {
    int initial_row = row;
    int initial_col = col;

    while (true) {
        if (direction > 0) { // Move right
            if (col < 2) {
                col++;
            } else if (row < 2) {
                col = 0;
                row++;
            } else { // Wrap around
                row = 0;
                col = 0;
            }
        } else if (direction < 0) { // Move left
            if (col > 0) {
                col--;
            } else if (row > 0) {
                col = 2;
                row--;
            } else { // Wrap around
                row = 2;
                col = 2;
            }
        }

        // Check if the new position is free
        if (!data[row][col].active && data[row][col].figure == -1) {
            break;
        }

        // If we wrap around to the initial position and it's still not free, stop searching
        if (row == initial_row && col == initial_col) {
            break;
        }
    }

    // Pack row and col into a single int
    return (row << 4) | col;
}



void get_move(unsigned char *mem_base, struct game_data data[3][3], bool player, int prev_pos, int current_pos) {
    int player_value = player ? 1 : 0; // Player 1 -> 1, Player 2 -> 0

    int prev_row = -1, prev_col = -1;

    // Find the active cell for the player
    for (unsigned int row = 0; row < 3; row++) {
        for (unsigned int col = 0; col < 3; col++) {
            if (data[row][col].figure == player_value && data[row][col].active) {
                prev_col = col;
                prev_row = row;
                break;
            }
        }
        if (prev_row != -1) {
            break;
        }
    }

    // Determine the movement direction
    int move_direction = current_pos - prev_pos;

    // Find the next free position in the specified direction
    int packed_pos = find_next_free(data, prev_row, prev_col, move_direction);
    int new_row = packed_pos >> 4;
    int new_col = packed_pos & 0xF;

    // Update the positions
    if (data[new_row][new_col].figure == -1) {
        data[new_row][new_col].figure = player_value;
        data[new_row][new_col].active = true;
        if (prev_row != -1 && prev_col != -1) {
            data[prev_row][prev_col].figure = -1;
            data[prev_row][prev_col].active = false;
        }
    }

//    printf("Player %d moved to (%d, %d)\n", player_value, new_row, new_col); // Debugging information
}


void save_move(struct game_data data[3][3],bool player) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (data[i][j].figure == player && data[i][j].active == true) {
                data[i][j].active = false;
                printf("Player %b saved to (%d, %d)\n", player, i, j); // Debugging information
                break;
            }
        }
    }
}

int minimax(struct game_data data[3][3], int depth, bool is_maximizing) {
    int score;
    int best_score;
    int winner = find_winner(data);

    if (winner == 1) {
        return 10 - depth; // Player 1 (human) wins
    } else if (winner == 0) {
        return depth - 10; // Player 2 (computer) wins
    } else if (check_draw(data)) {
        return 0; // Draw
    }

    if (is_maximizing) {
        best_score = -1000;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (data[row][col].figure == -1) {
                    data[row][col].figure = 1; // Human's move
                    score = minimax(data, depth + 1, false);
                    data[row][col].figure = -1;
                    best_score = (score > best_score) ? score : best_score;
                }
            }
        }
        return best_score;
    } else {
        best_score = 1000;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (data[row][col].figure == -1) {
                    data[row][col].figure = 0; // Computer's move
                    score = minimax(data, depth + 1, true);
                    data[row][col].figure = -1;
                    best_score = (score < best_score) ? score : best_score;
                }
            }
        }
        return best_score;
    }
}


void computers_move(struct game_data data[3][3]) {
    int best_score = 1000; // Minimax function prefers minimizing for the computer
    int move_row = -1;
    int move_col = -1;

    // Find the best move for the new figure
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (data[row][col].figure == -1) { // Check if the cell is empty
                data[row][col].figure = 0; // Make the move (computer is O)
                int score = minimax(data, 0, true); // Call minimax
                data[row][col].figure = -1; // Undo the move

                if (score < best_score) {
                    best_score = score;
                    move_row = row;
                    move_col = col;
                }
            }
        }
    }

    if (move_row != -1 && move_col != -1) {
        data[move_row][move_col].figure = 0; // Make the best move (computer is O)
        data[move_row][move_col].active = false;
        printf("Computer placed at (%d, %d)\n", move_row, move_col); // Debugging information
    }
}
