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
    start_color();
    init_colors();
    int sx, sy;
    getmaxyx(stdscr, sy, sx);

    Game game;

    game.display();


    getch();

    endwin();

    return 0;
}