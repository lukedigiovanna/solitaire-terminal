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

    std::unique_ptr<Deck> deck = std::make_unique<StandardDeck>();

    deck->shuffle();

    for (auto c : *deck) {
        c.display(COLOR_WHITE, COLOR_CYAN, rand() % sx, rand() % sy);
    }


    getch();

    endwin();

    return 0;
}