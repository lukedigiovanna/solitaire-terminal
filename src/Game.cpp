#include "Game.h"
#include "mathutils.h"
#include <iostream>
#include <ncursesw/curses.h>

using namespace std;

inline bool isTableau(GameElement element) {
    return element >= GameElement::TABLEAU_0 && element <= GameElement::TABLEAU_6;
}

inline int getTableauIndex(GameElement element) {
    return static_cast<int>(element) - static_cast<int>(GameElement::TABLEAU_0);
}

inline bool isFoundation(GameElement element) {
    return element >= GameElement::FOUNDATION_0 && element <= GameElement::FOUNDATION_3;
}

inline int getFoundationIndex(GameElement element) {
    return static_cast<int>(element) - static_cast<int>(GameElement::FOUNDATION_0);
}

Game::Game() {
    deck = std::make_unique<StandardDeck>();
    deck->shuffle();

    turnedDeck = std::make_unique<Deck>();
    
    for (int i = 0; i < 7; i++) {
        tableaus[i] = std::make_unique<Deck>();
    }

    for (int i = 0; i < 4; i++) {
        foundations[i] = std::make_unique<Deck>();
    }

    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j--;) {
            tableaus[i]->addCardTop(deck->drawCardTop());
        }
        tableauPositions[i] = i;
    }
}

void Game::display(UIControls controls) const {
    clear();

    int tx, ty;

    tx = 3;
    ty = 1;

    if (deck->size() > 0) {
        wmove(stdscr, tx, ty);
        Card::display_back(
            controls.bgBackColor(GameElement::DRAW_STACK, true), controls.fgBackColor(GameElement::DRAW_STACK), tx, ty
        );
    }
    else {
        Card::display_empty(
            controls.bgEmptyColor(GameElement::DRAW_STACK), controls.fgEmptyColor(GameElement::DRAW_STACK), tx, ty
        );
    }

    tx += CARD_WIDTH + 2;

    wmove(stdscr, tx, ty);
    if (turnedDeck->size() > 0) {
        turnedDeck->getTopCard().display(
            controls.bgCardColor(GameElement::WASTE_STACK), controls.fgCardColor(GameElement::WASTE_STACK), tx, ty
        );
    }
    else {
        Card::display_empty(
            controls.bgEmptyColor(GameElement::WASTE_STACK), controls.fgEmptyColor(GameElement::WASTE_STACK), tx, ty
        );
    }

    tx += (CARD_WIDTH + 2) * 2;
    for (int i = 0; i < 4; i++) {
        GameElement element = static_cast<GameElement>(static_cast<int>(GameElement::FOUNDATION_0) + i);
        if (foundations[i]->size() == 0) {
            Card::display_empty(
                controls.bgEmptyColor(element), controls.fgEmptyColor(element), tx, ty
            );
        }
        else {
            foundations[i]->getTopCard().display(
                controls.bgCardColor(element), controls.fgCardColor(element), tx, ty
            );
        }
        tx += CARD_WIDTH + 2;
    }

    for (int i = 0; i < 7; i++) {
        tx = 3 + i * (CARD_WIDTH + 2);
        ty = 1 + 1 + CARD_HEIGHT;
        GameElement element = static_cast<GameElement>(static_cast<int>(GameElement::TABLEAU_0) + i);
        if (tableaus[i]->size() == 0) {
            Card::display_empty(controls.bgEmptyColor(element), controls.fgEmptyColor(element), tx, ty);
        }
        else {
            for (int j = 0; j < tableaus[i]->size(); j++) {
                if (j < tableauPositions[i]) {
                    Card::display_back(controls.bgBackColor(element, false), controls.fgBackColor(element), tx, ty);
                }
                else {
                    (*tableaus[i])[j].display(
                        controls.bgCardColor(element, j), controls.fgCardColor(element), tx, ty
                    );
                }
                ty += 2;
            }
        }
    }
}

int Game::getTableauPosition(int idx) const {
    return tableauPositions[idx];
}

size_t Game::getTableauSize(int idx) const {
    return tableaus[idx]->size();
}

size_t Game::getFoundationSize(int idx) const {
    return foundations[idx]->size();
}

size_t Game::getWasteStackSize() const {
    return turnedDeck->size();
}

void Game::drawCard() {
    if (deck->size() == 0) {
        while (turnedDeck->size() > 0)
            deck->addCardTop(turnedDeck->drawCardTop());
    }
    else {
        turnedDeck->addCardTop(deck->drawCardTop());
    }
}

bool Game::move(GameElement from, GameElement to, int quantity) {
    // Can transfer up 1 card to a foundation at a time.
    if (isFoundation(to) && quantity > 1) {
        return false;
    }

    // Cannot transfer to the draw or waste stacks
    if (to == GameElement::WASTE_STACK || to == GameElement::DRAW_STACK) {
        return false;
    }

    // Consider different possibilities
    const Card* moveCard = nullptr; // The card that dictates whether the move is legal
    if (isTableau(from)) {
        int idx = getTableauIndex(from);
        moveCard = &((*tableaus[idx])[getTableauSize(idx) - quantity]);
    }
    else if (isFoundation(from)) {
        int idx = getFoundationIndex(from);
        moveCard = &((*foundations[idx])[getFoundationSize(idx) - 1]);
    }
    else if (from == GameElement::WASTE_STACK) {
        moveCard = &((*turnedDeck)[turnedDeck->size() - 1]);
    }

    if (isTableau(to)) {
        // Then the from card must be able to rest on top of the top card of the tableau
        int toIdx = getTableauIndex(to);
        const Card* topCard = nullptr;
        if (getTableauSize(toIdx) > 0)
            topCard = &((*tableaus[toIdx])[getTableauSize(toIdx) - 1]);
        // Now check if it is a legal
        if ((topCard == nullptr && moveCard->value == 12) || (topCard != nullptr && moveCard->suit.color != topCard->suit.color && moveCard->value == topCard->value - 1)) {
            // Perform the transfer
            if (isTableau(from)) {
                int fromIdx = getTableauIndex(from);
                for (size_t i = getTableauSize(fromIdx) - quantity; i < getTableauSize(fromIdx); i++)
                    tableaus[toIdx]->addCardTop((*tableaus[fromIdx])[i]);
                for (int i = 0; i < quantity; i++)
                    tableaus[fromIdx]->drawCardTop();
                
                if (tableauPositions[fromIdx] >= tableaus[fromIdx]->size()) {
                    tableauPositions[fromIdx] = tableaus[fromIdx]->size() - 1;
                }
            }
            else if (isFoundation(from)) {
                int fromIdx = getFoundationIndex(from);
                tableaus[toIdx]->addCardTop(*moveCard);
                foundations[fromIdx]->drawCardTop();
            }
            else if (from == GameElement::WASTE_STACK) {
                tableaus[toIdx]->addCardTop(*moveCard);
                turnedDeck->drawCardTop();
            }
            return true;
        }
        else { // Otherwise it was illegal
            return false;
        }
    }
    
    if (isFoundation(to)) {
        int toIdx = getFoundationIndex(to);
        const Card* topCard = nullptr;
        if (getFoundationSize(toIdx) > 0)
            topCard = &((*foundations[toIdx])[getFoundationSize(toIdx) - 1]);
        if ((topCard == nullptr && moveCard->value == 0) || (moveCard->value == topCard->value + 1 && moveCard->suit.symbol == topCard->suit.symbol)) {
            foundations[toIdx]->addCardTop(*moveCard);
            if (isTableau(from)) {
                int fromIdx = getTableauIndex(from);
                tableaus[fromIdx]->drawCardTop();
                if (tableauPositions[fromIdx] >= tableaus[fromIdx]->size()) {
                    tableauPositions[fromIdx] = tableaus[fromIdx]->size() - 1;
                }
            }
            else if (from == GameElement::WASTE_STACK) {
                turnedDeck->drawCardTop();
            }
            return true;
        }
        else {
            return false;
        }
    }

    return false;
}

bool Game::move(GameElement from, GameElement to) {
    return move(from, to, 1);
}

UIControls::UIControls(Game& game, ColorTheme theme) : 
    game(game), 
    current(GameElement::DRAW_STACK), 
    tableauRow(0),
    entered(false),
    theme(theme) {

}

bool UIControls::selected(GameElement element) const {
    return current == element;
}

void UIControls::move(int d) {
    int nc = static_cast<int>(current) + d;
    if (isTableau(current)) {
        nc = wrap(nc, static_cast<int>(GameElement::TABLEAU_0), static_cast<int>(GameElement::TABLEAU_6));
    }
    else {
        nc = wrap(nc, static_cast<int>(GameElement::DRAW_STACK), static_cast<int>(GameElement::FOUNDATION_3));
    }
    current = static_cast<GameElement>(nc);
    tableauRow = 0;
}

void UIControls::moveRight() {
    move(1);
}

void UIControls::moveLeft() {
    move(-1);
}

void UIControls::moveUp() {
    if (isTableau(current)) {
        int tableauIndex = getTableauIndex(current);
        int position = game.getTableauPosition(tableauIndex);
        int size = game.getTableauSize(tableauIndex);
        int max = size - 1 - position;
        tableauRow++;
        if (tableauRow > max) tableauRow = max;
    }
}

void UIControls::moveDown() {
    tableauRow--;
    if (tableauRow < 0) tableauRow = 0;
}

void UIControls::toggleTableau() {
    int nc = static_cast<int>(current);
    if (isTableau(current)) {
        if (current >= GameElement::TABLEAU_3)
            nc--;
        nc -= static_cast<int>(GameElement::TABLEAU_0);
    }
    else {
        if (current >= GameElement::FOUNDATION_0)
            nc++;
        nc += static_cast<int>(GameElement::TABLEAU_0);
    }
    current = static_cast<GameElement>(nc);
}

void UIControls::selectCurrent() {
    if (entered) {
        if (isTableau(enteredElement)) {
            game.move(enteredElement, current, enteredTableauRow + 1);
        }
        else {
            game.move(enteredElement, current);
        }
        entered = false;
    }
    else if (current == GameElement::DRAW_STACK) {
        entered = false;
        game.drawCard();
    }
    else {
        // Check if we cannot enter on the current element
        if (isTableau(current)) {
            int idx = getTableauIndex(current);
            if (game.getTableauSize(idx) == 0) 
                return;
        }
        else if (isFoundation(current)) {
            int idx = getFoundationIndex(current);
            if (game.getFoundationSize(idx) == 0)
                return;
        }
        else if (current == GameElement::WASTE_STACK) {
            if (game.getWasteStackSize() == 0)
                return;
        }
        entered = true;
        enteredElement = current;
        enteredTableauRow = tableauRow;
    }
}

int UIControls::fgBackColor(GameElement element) const {
    return COLOR_WHITE;
}

int UIControls::bgBackColor(GameElement element, bool selectable) const {
    if (selectable) {
        if (entered && enteredElement == element)
            return theme.enteredColor;
        if (current == element)
            return theme.highlightColor;
    }
    return theme.bgColor;
}

int UIControls::fgEmptyColor(GameElement element) const {
    if (current == element)
        return theme.highlightColor;
    return COLOR_WHITE;
}

int UIControls::bgEmptyColor(GameElement element) const {
    return COLOR_BLACK;
}

int UIControls::fgCardColor(GameElement element) const {
    return theme.fgColor;
}

int UIControls::bgCardColor(GameElement element) const {
    if (entered && enteredElement == element)
        return theme.enteredColor;
    if (current == element) {
        return theme.highlightColor;
    }
    return COLOR_WHITE;
}

int UIControls::bgCardColor(GameElement element, int j) const {
    if (!isTableau(element))
        return bgCardColor(element);

    int idx = getTableauIndex(element);
    int size = game.getTableauSize(idx);
    
    if (entered && enteredElement == element && size - 1 - j <= enteredTableauRow) {
        return theme.enteredColor;
    }
    
    if (current == element && size - 1 - j <= tableauRow) {
        return theme.highlightColor;
    }

    return COLOR_WHITE;
}