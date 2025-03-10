#include "drawing.h"
#include "utils.h"
#include "game.h"
#include "game_objects.h"

void draw_figures(struct game_data data[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (data[i][j].figure == 1) {
                draw_x(data[i][j].x_pos, data[i][j].y_pos);
            } else if (data[i][j].figure == 0) {
                draw_o(data[i][j].x_pos, data[i][j].y_pos);
            }
        }
    }
}

void draw_x(int x, int y) {
    unsigned int x_color = hsv2rgb_lcd(60, 255, 255); // Color for X
    for (int i = -20; i <= 20; i++) {
        draw_pixel_big(x + i, y + i, x_color, 10);
        draw_pixel_big(x + i, y - i, x_color, 10);
    }
}

void draw_o(int x, int y) {
    unsigned int o_color = hsv2rgb_lcd(210, 255, 255); // Color for O
    draw_empty_circle(x, y, 20, o_color, 10);
}

#include "game_objects.h"
