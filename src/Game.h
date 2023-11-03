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
        vector<char> tableaus[7];
        int tableauPositions[7]; // marks the first card that is face up
        int piles[4];
        int currCard;

        bool executeDrawCard();
        bool executeMove(int from, int to, int quantity);
    public:
        Game(); // Construct a random state of the game

        void display() const;

        bool execute(Action action);
};  