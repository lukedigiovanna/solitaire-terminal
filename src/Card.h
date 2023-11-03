#pragma once

#include <string>

#define CARD_WIDTH 14
#define CARD_HEIGHT 10

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

        Card(Suit suit, int value);
        void display(int bg_color, int fg_color, int tx, int ty) const;
};
