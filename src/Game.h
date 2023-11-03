#pragma once

#include "Deck.h"

#include <vector>
#include <string>

using namespace std;

enum ActionType {
    DRAW_CARD,
    MOVE
};

struct Action {
    ActionType type;
    int from;
    int to;
    int quantity;
};

class Game {
    private:
        vector<Action> history;
        std::unique_ptr<Deck> deck;
        std::unique_ptr<Deck> turnedDeck;
        std::unique_ptr<Deck> tableaus[7];
        int tableauPositions[7]; // marks the first card that is face up
        std::unique_ptr<Deck> piles[4];

        bool executeDrawCard();
        bool executeMove(int from, int to, int quantity);
    public:
        Game(); // Construct a random state of the game

        void display() const;

        bool execute(Action action);
};  