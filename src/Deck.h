#pragma once

#include <vector>
#include "Card.h"

using namespace std;

class Deck {
    protected:
        vector<Card> cards;
    public:
        Deck();

        void shuffle();
        size_t size() const;
        // Gets the top card but does not remove it
        Card getTopCard();
        // Draws a card from the top of the stack and returns it
        Card drawCardTop();
        // Draws a card from the bottom of the stack
        // Card draw_card_bottom();
        // Adds a card to the top of the stack
        void addCardTop(Card c);
        // Adds a card to the bottom of the stack
        // void add_card_bottom(Card c);

        // Implement a begin/end methods to be able to iterate over the deck
        vector<Card>::const_iterator begin() const;
        vector<Card>::const_iterator end() const;

        const Card& operator[](size_t index) const;
};

// Standard deck initializes with all cards
class StandardDeck : public Deck {
    public:
        StandardDeck();
};