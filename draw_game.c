#include "drawing.h"
#include "utils.h"
#include "game.h"
#include "game_objects.h"
#include "draw_game.h"

extern unsigned short *fb;

void draw_empty_board() {
    for (int ptr = 0; ptr < 320 * 480; ptr++) {
        unsigned int col = hsv2rgb_lcd(260, 0, 70);
        fb[ptr] = col;

    }
    for (int i = 0; i < 480; i++) {
        unsigned int col = hsv2rgb_lcd(0, 0, 255);
        if (i == 0 || i == 476) {
            for (int j = 0; j < 320; j++)
                draw_pixel_big(i, j, col, 4);
        } else {
            draw_pixel_big(i, 0, col, 4);
            draw_pixel_big(i, 316, col, 4);
        }
    }
}

void draw_board_background() {
    unsigned int background_color = hsv2rgb_lcd(0, 0, 255); // Background color
    // Fill the background
    for (int ptr = 0; ptr < 320 * 480; ptr++) {
        fb[ptr] = background_color;
    }
}

void draw_board() {
    unsigned int line_color = hsv2rgb_lcd(0, 0, 0); // Line color

    // Draw vertical lines
    for (int i = 0; i < 320; i++) {
        draw_pixel_big(160, i, line_color, 7); // First vertical line
        draw_pixel_big(320, i, line_color, 7); // Second vertical line
    }

    // Draw horizontal lines
    for (int i = 0; i < 480; i++) {
        draw_pixel_big(i, 106, line_color, 7); // First horizontal line
        draw_pixel_big(i, 213, line_color, 7); // Second horizontal line
    }
}
