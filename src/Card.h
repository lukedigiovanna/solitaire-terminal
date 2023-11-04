#pragma once

#include <string>

#define CARD_WIDTH 15
#define CARD_HEIGHT 11

enum Color {
    BLACK,
    RED
};

struct Suit {
    std::wstring symbol;
    Color color;

    static const Suit HEARTS;
    static const Suit DIAMONDS;
    static const Suit SPADES;
    static const Suit CLUBS;
};

class Card {
    private:
        Suit suit;
        int value;
    public:
        static const std::wstring value_titles[];

        static void display_back(int bg_color, int fg_color, int tx, int ty);
        static void display_empty(int bg_color, int fg_color, int tx, int ty);

        Card(Suit suit, int value);
        void display(int bg_color, int fg_color, int tx, int ty) const;
};
