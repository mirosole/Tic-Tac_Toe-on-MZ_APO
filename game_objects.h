#include <stdbool.h>

#ifndef TICTACTOE_GAME_OBJECTS_H
#define TICTACTOE_GAME_OBJECTS_H

struct game_data {
    bool active;
    int x_pos;
    int y_pos;
    int figure; // -1 - empty, 1 - X, 0 - O
};

void draw_figures (struct game_data data[3][3]);

void draw_x(int x, int y);

void draw_o(int x, int y);

#endif //TICTACTOE_GAME_OBJECTS_H
