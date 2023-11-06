#include "Card.h"
#include "Game.h"
#include "Deck.h"
#include "termutils.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <memory>
#include <unistd.h>

#include <ncursesw/curses.h>
#include <locale>


int main() {
    srand(time(0));

    setlocale(LC_ALL, "");
    std::locale::global(std::locale(""));

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    set_escdelay(25);
    start_color();
    init_colors();
    int sx, sy;
    getmaxyx(stdscr, sy, sx);

    Game game;
    ColorTheme theme = {
        .bgColor=COLOR_RED,
        .fgColor=COLOR_BLACK,
        .enteredColor=COLOR_YELLOW,
        .highlightColor=COLOR_GREEN
    };
    UIControls controls = UIControls(game, theme);

    game.display(controls);

    bool quit = false;

    while (!quit) {
        int ch = getch();

        switch (ch) {
            case KEY_RIGHT:
                controls.moveRight();
                break;
            case KEY_LEFT:
                controls.moveLeft();
                break;
            case KEY_UP:
                controls.moveUp();
                break;
            case KEY_DOWN:
                controls.moveDown();
                break;
            case 10: // Enter
                controls.selectCurrent();
                break;
            case ' ':
            case 9: // Horizontal tab
                controls.toggleTableau();
                break;
            case 27: // Escape key
                quit = true;
        }

        game.display(controls);

        refresh();
    }

    endwin();

    return 0;
}