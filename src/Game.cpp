#include "Game.h"
#include "mathutils.h"
#include <iostream>
#include <ncursesw/curses.h>

using namespace std;

Game::Game() {
    deck = std::make_unique<StandardDeck>();
    deck->shuffle();

    turnedDeck = std::make_unique<Deck>();
    
    for (int i = 0; i < 7; i++) {
        tableaus[i] = std::make_unique<Deck>();
    }

    for (int i = 0; i < 4; i++) {
        piles[i] = std::make_unique<Deck>();
    }

    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j--;) {
            tableaus[i]->add_card_top(deck->draw_card_top());
        }
        tableauPositions[i] = 0;
    }
}

void Game::display(UIControls controls) const {
    static int HIGHLIGHT_COLOR = COLOR_GREEN;
    wmove(stdscr, 0, 0);
    addwstr(to_wstring(static_cast<int>(controls.current)).c_str());
    wmove(stdscr, 1, 0);
    addwstr(to_wstring(static_cast<int>(-1 % 2)).c_str());
    
    int tx, ty;

    tx = 3;
    ty = 3;

    if (deck->size() > 0) {
        wmove(stdscr, tx, ty);
        Card::display_back(controls.selected(GameElement::DRAW_STACK) ? HIGHLIGHT_COLOR : COLOR_RED, COLOR_WHITE, tx, ty);
    }
    else {
        Card::display_empty(COLOR_BLACK, controls.selected(GameElement::DRAW_STACK) ? HIGHLIGHT_COLOR : COLOR_WHITE, tx, ty);
    }

    tx += CARD_WIDTH + 2;

    wmove(stdscr, tx, ty);
    if (turnedDeck->size() > 0) {
        turnedDeck->get_top_card().display(controls.selected(GameElement::WASTE_STACK) ? HIGHLIGHT_COLOR : COLOR_WHITE, COLOR_CYAN, tx, ty);
    }
    else {
        Card::display_empty(COLOR_BLACK, controls.selected(GameElement::WASTE_STACK) ? HIGHLIGHT_COLOR : COLOR_WHITE, tx, ty);
    }

    tx += (CARD_WIDTH + 2) * 2;
    for (int i = 0; i < 4; i++) {
        bool selected = controls.selected(static_cast<GameElement>(static_cast<int>(GameElement::FOUNDATION_CLUBS) + i));
        Card::display_empty(
            COLOR_BLACK, 
            selected ? HIGHLIGHT_COLOR : COLOR_WHITE, 
            tx, 
            ty
        );
        tx += CARD_WIDTH + 2;
    }

    for (int i = 0; i < 7; i++) {
        tx = 3 + i * (CARD_WIDTH + 2);
        ty = 3 + 2 + CARD_HEIGHT;
        for (int j = 0; j < tableaus[i]->size(); j++) {
            if (j < tableauPositions[i]) {
                Card::display_back(COLOR_RED, COLOR_WHITE, tx, ty);
            }
            else {
                bool selected = controls.selected(static_cast<GameElement>(static_cast<int>(GameElement::TABLEAU_0) + i));
                selected &= controls.tableauRow >= tableaus[i]->size() - 1 - j;
                (*tableaus[i])[j].display(selected ? HIGHLIGHT_COLOR : COLOR_WHITE, COLOR_BLACK, tx, ty);
            }
            ty += 2;
        }
    }
}

const std::array<int, 7>& Game::getTableauPositions() const {
    return tableauPositions;
}

bool Game::execute(Action action) {
    bool success = false;
    switch (action.type) {
        case DRAW_CARD:
            success |= executeDrawCard();
            break;
        case MOVE:
            success |= executeMove(action.from, action.to, action.quantity);
            break;
    }

    if (success) {
        history.push_back(action);
    }

    return success;
}

bool Game::executeDrawCard() {
    // currCard = (currCard + 1) % (deck.size() + 1);
    return true;
}

bool Game::executeMove(int from, int to, int quantity) {
    // 0-6 are tableaus, 7-10 are the piles, 11 is the draw stack
    cout << "Executing MOVE of " << quantity << " from " << from << " to " << to << endl;
    if (from == 11) {

    }
    return false;
}

UIControls::UIControls() : current(GameElement::DRAW_STACK), tableauRow(0) {

}

bool UIControls::selected(GameElement element) const {
    return current == element;
}

void UIControls::move(int d) {
    int nc = static_cast<int>(current) + d;
    if (isTableau()) {
        nc = wrap(nc, static_cast<int>(GameElement::TABLEAU_0), static_cast<int>(GameElement::TABLEAU_6));
    }
    else {
        nc = wrap(nc, static_cast<int>(GameElement::DRAW_STACK), static_cast<int>(GameElement::FOUNDATION_SPADES));
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

void UIControls::moveUp(const Game& game) {
    tableauRow++;
}

void UIControls::moveDown() {
    tableauRow--;
    if (tableauRow < 0) tableauRow = 0;
}

void UIControls::toggleTableau() {
    int nc = static_cast<int>(current);
    if (isTableau()) {
        if (current == GameElement::TABLEAU_6) { // special case
            current = GameElement::FOUNDATION_SPADES;
            return;
        }
        nc -= static_cast<int>(GameElement::TABLEAU_0);
    }
    else {
        nc += static_cast<int>(GameElement::TABLEAU_0);
    }
    current = static_cast<GameElement>(nc);
}

bool UIControls::isTableau() const {
    return current >= GameElement::TABLEAU_0 && current <= GameElement::TABLEAU_6;
}