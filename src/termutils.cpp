#include "termutils.h"
#include <ncursesw/curses.h>

static int cur_color = 0;

static int saved_color;

void init_colors() {
    for (short c1 = 0; c1 < 8; c1++) {
        for (short c2 = 0; c2 < 8; c2++) {
            short pair_num = c1 | (c2 << 3);
            init_pair(pair_num, c1, c2);
        }
    }
    set_fg_color(COLOR_WHITE);
    set_bg_color(COLOR_BLACK);

    save_color();
}

void save_color() {
    saved_color = cur_color;
}

void restore_color() {
    set_color(saved_color);
}

void set_fg_color(int color) {
    cur_color = (0b111000 & cur_color) | color;
    attron(COLOR_PAIR(cur_color));
}

void set_bg_color(int color) {
    cur_color = (0b111 & cur_color) | (color << 3);
    attron(COLOR_PAIR(cur_color));
}

void set_color_pair(int fg_color, int bg_color) {
    set_fg_color(fg_color);
    set_bg_color(bg_color);
}

void reverse_color() {
    int fg = cur_color & 0b111;
    int bg = cur_color >> 3;
    set_color_pair(bg, fg);
}

void set_color(int color) {
    cur_color = color;
    attron(COLOR_PAIR(cur_color));
}