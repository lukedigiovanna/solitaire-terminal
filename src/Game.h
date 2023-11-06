#pragma once

#include "Deck.h"

#include <vector>
#include <string>

using namespace std;

enum ActionType {
    DRAW_CARD,
    MOVE
};

enum class GameElement {
    DRAW_STACK,
    WASTE_STACK,
    FOUNDATION_0,
    FOUNDATION_1,
    FOUNDATION_2,
    FOUNDATION_3,
    TABLEAU_0,
    TABLEAU_1,
    TABLEAU_2,
    TABLEAU_3,
    TABLEAU_4,
    TABLEAU_5,
    TABLEAU_6,
    NUM_ELEMENTS // This will keep track of the number of elements
};

static inline bool isTableau(GameElement element);
static inline int getTableauIndex(GameElement element);
static inline bool isFoundation(GameElement element);
static inline int getFoundationIndex(GameElement element);

class UIControls; // Forward declare class

class Game {
    private:
        std::unique_ptr<Deck> deck;
        std::unique_ptr<Deck> turnedDeck;
        std::unique_ptr<Deck> tableaus[7];
        std::array<int, 7> tableauPositions; // marks the first card that is face up
        std::unique_ptr<Deck> foundations[4];
    public:
        Game(); // Construct a random state of the game

        void display(UIControls controls) const;

        int getTableauPosition(int idx) const;
        size_t getTableauSize(int idx) const; 
        size_t getFoundationSize(int idx) const;
        size_t getWasteStackSize() const;

        void drawCard();
        bool move(GameElement from, GameElement to, int quantity);
        bool move(GameElement from, GameElement to);
};

struct ColorTheme {
    int highlightColor;
    int enteredColor;
    int bgColor;
    int fgColor;
};

class UIControls {
    private:
        Game& game;
        void move(int d);
        ColorTheme theme;
    public:
        GameElement current;
        int tableauRow;
        bool entered;
        GameElement enteredElement;
        int enteredTableauRow;

        UIControls(Game& game, ColorTheme theme);

        void moveRight();
        void moveLeft();
        void moveUp();
        void moveDown();
        void toggleTableau();

        void selectCurrent();

        bool selected(GameElement element) const;

        int fgBackColor(GameElement element) const;
        int bgBackColor(GameElement element, bool selectable) const;
        int fgEmptyColor(GameElement element) const;
        int bgEmptyColor(GameElement element) const;
        int fgCardColor(GameElement element) const;
        int bgCardColor(GameElement element) const;
        int bgCardColor(GameElement element, int j) const;
};