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

enum class GameElement {
    DRAW_STACK,
    WASTE_STACK,
    FOUNDATION_CLUBS,
    FOUNDATION_DIAMONDS,
    FOUNDATION_HEARTS,
    FOUNDATION_SPADES,
    TABLEAU_0,
    TABLEAU_1,
    TABLEAU_2,
    TABLEAU_3,
    TABLEAU_4,
    TABLEAU_5,
    TABLEAU_6,
    NUM_ELEMENTS // This will keep track of the number of elements
};

class UIControls; // Forward declare class

class Game {
    private:
        vector<Action> history;
        std::unique_ptr<Deck> deck;
        std::unique_ptr<Deck> turnedDeck;
        std::unique_ptr<Deck> tableaus[7];
        std::array<int, 7> tableauPositions; // marks the first card that is face up
        std::unique_ptr<Deck> piles[4];

        bool executeDrawCard();
        bool executeMove(int from, int to, int quantity);
    public:
        Game(); // Construct a random state of the game

        void display(UIControls controls) const;

        const std::array<int, 7>& getTableauPositions() const;    

        bool execute(Action action);
};  

class UIControls {
    private:
        void move(int d);
        bool isTableau() const;
    public:
        GameElement current;
        int tableauRow;

        UIControls();

        void moveRight();
        void moveLeft();
        void moveUp(const Game& game);
        void moveDown();
        void toggleTableau();

        bool selected(GameElement element) const;
};