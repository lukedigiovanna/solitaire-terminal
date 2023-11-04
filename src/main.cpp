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
    start_color();
    init_colors();
    int sx, sy;
    getmaxyx(stdscr, sy, sx);

    Game game;
    UIControls controls;

    game.display(controls);

    while (1) {
        int ch = getch();

        switch (ch) {
            case KEY_RIGHT:
                controls.moveRight();
                break;
            case KEY_LEFT:
                controls.moveLeft();
                break;
            case KEY_UP:
                controls.moveUp(game);
                break;
            case KEY_DOWN:
                controls.moveDown();
                break;
            case ' ':
                controls.toggleTableau();
                break;
        }

        game.display(controls);

        refresh();
    }

    endwin();

    return 0;
}