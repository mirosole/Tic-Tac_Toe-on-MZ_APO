#include <stdbool.h>

#include "utils.h"
#include "game.h"
#include "game_objects.h"
#include "checker_game.h"

extern int diffNum;

/**
 * @brief Checks if a player has won.
 *
 * @param data The game board data.
 * @param player The player for which to check win status (1 for Player 1, 0 for Player 2).
 * @return true if the player's moves make a winning tic-tac-toe combination.
 */
bool is_winner(const struct game_data data[3][3], int player) {
    unsigned int i, j, board_size = 3;

    // check rows
    for (i = 0; i < board_size; ++i) {
        for (j = 0; j < board_size; ++j) {
            if (data[i][j].figure != player)
                break;

            if (j == board_size - 1)
                return true;
        }
    }

    // check columns
    for (i = 0; i < board_size; ++i) {
        for (j = 0; j < board_size; ++j) {
            if (data[j][i].figure != player)
                break;

            if (j == board_size - 1)
                return true;
        }
    }

    // check diagonal from top-left to bottom-right
    for (i = 0; i < board_size; ++i) {
        if (data[i][i].figure != player)
            break;

        if (i == board_size - 1)
            return true;
    }

    // check diagonal from top-right to bottom-left
    for (i = 0; i < board_size; ++i) {
        if (data[i][board_size - 1 - i].figure != player)
            break;

        if (i == board_size - 1)
            return true;
    }

    return false;
}


/**
 * @brief Finds the winner of the game.
 *
 * @param data The game board data.
 * @return The player who wins (1 for Player 1, 0 for Player 2) or -1 if no winner.
 */
int find_winner(const struct game_data data[3][3]) {
    static const int players[] = {1, 0};

    for (unsigned int i = 0; i < 2; ++i) {
        if (is_winner(data, players[i])) {
            return players[i];
        }
    }

    return -1; // No winner
}


/**
 * @brief Checks if there is a winner and updates the win counters.
 *
 * @param data The game board data.
 * @param num_win_round_blue Pointer to the number of wins for Player 1 (blue).
 * @param num_win_round_red Pointer to the number of wins for Player 2 (red).
 * @return true if there is a winner, false otherwise.
 */
bool check_win(struct game_data data[3][3], int *num_win_round_blue, int *num_win_round_red) {
    int winner = find_winner(data);

    if (winner == 0) { // Player 1 wins
        *num_win_round_blue = *num_win_round_blue + 1;
        return true;
    } else if (winner == 1) { // Player 2 wins
        *num_win_round_red = *num_win_round_red + 1;
        return true;
    }
    return false;
}

bool check_draw(struct game_data data[3][3]) {
    // Check if the board is full
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (data[row][col].figure == -1) {
                return false; // Found an empty cell, so not a draw
            }
        }
    }

    // Check if there is no winner
    if (find_winner(data) == -1) {
        return true; // Board is full and no winner, so it's a draw
    }

    return false; // Board is full, but there is a winner
}
