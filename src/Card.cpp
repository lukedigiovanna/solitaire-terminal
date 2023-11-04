#include "Card.h"
#include <iostream>
#include <ncursesw/curses.h>

#include "termutils.h"

const Suit Suit::HEARTS = { L"\u2665", RED };
const Suit Suit::DIAMONDS = { L"\u2666", RED };
const Suit Suit::SPADES = { L"\u2660", BLACK };
const Suit Suit::CLUBS = { L"\u2663", BLACK };

const std::wstring Card::value_titles[] = {
    L"A", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"10", L"J", L"Q", L"K"
};

Card::Card(Suit suit, int value) : suit(suit), value(value) {}

void Card::display_back(int bg_color, int fg_color, int tx, int ty) {
    save_color();
    set_bg_color(bg_color);
    set_fg_color(fg_color);
    wmove(stdscr, ty + 0, tx);
    addwstr(L"╔═════════════╗");
    for (int i = 1; i <= CARD_HEIGHT - 2; i++) {
        wmove(stdscr, ty + i, tx);
        if (i & 1) {
            addwstr(L"║ ░ ░ ░ ░ ░ ░ ║");
        }
        else {
            addwstr(L"║░ ░ ░ ░ ░ ░ ░║");
        }
    }
    wmove(stdscr, ty + CARD_HEIGHT - 1, tx);
    addwstr(L"╚═════════════╝");
    restore_color();
}

void Card::display_empty(int bg_color, int fg_color, int tx, int ty) {
    save_color();
    set_bg_color(bg_color);
    set_fg_color(fg_color);
    wmove(stdscr, ty + 0, tx);
    addwstr(L"╔ ═ ═ ═ ═ ═ ═ ╗");
    for (int i = 1; i <= CARD_HEIGHT - 2; i++) {
        wmove(stdscr, ty + i, tx);
        if (i & 1) {
            addwstr(L"║              ");
        }
        else {
            addwstr(L"              ║");
        }
    }
    wmove(stdscr, ty + CARD_HEIGHT - 1, tx);
    addwstr(L"╚═ ═ ═ ═ ═ ═ ═╝");
    restore_color();
}

void Card::display(int bg_color, int fg_color, int tx, int ty) const {
    save_color();
    set_bg_color(bg_color);
    set_fg_color(fg_color);
    wmove(stdscr, ty, tx);
    addwstr(L"╔═════════════╗");
    for (int i = 1; i <= CARD_HEIGHT - 2; i++) {
        wmove(stdscr, ty + i, tx);
        addwstr(L"║             ║");
    }
    wmove(stdscr, ty + CARD_HEIGHT - 1, tx);
    addwstr(L"╚═════════════╝");

    wmove(stdscr, ty + 1, tx + 2);
    addwstr(value_titles[value].c_str());
    wmove(stdscr, ty + CARD_HEIGHT - 2, tx + CARD_WIDTH - 2 - value_titles[value].size());
    addwstr(value_titles[value].c_str());

    if (suit.color == RED) 
        set_fg_color(COLOR_RED);
    else if (suit.color == BLACK) 
        set_fg_color(COLOR_BLACK);
    wmove(stdscr, ty + 1, tx + 2 + value_titles[value].size());
    addwstr(suit.symbol.c_str());
    wmove(stdscr, ty + CARD_HEIGHT - 2, tx + CARD_WIDTH - 3 - value_titles[value].size());
    addwstr(suit.symbol.c_str());

    restore_color();
}