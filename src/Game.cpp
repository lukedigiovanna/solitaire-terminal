#include "Game.h"
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
        tableauPositions[i] = i;
    }
}

void Game::display() const {
    int tx, ty;

    tx = 3;
    ty = 3;

    if (deck->size() > 0) {
        wmove(stdscr, tx, ty);
        Card::display_back(COLOR_RED, COLOR_WHITE, tx, ty);
    }

    tx += CARD_WIDTH + 1;

    if (turnedDeck->size() > 0) {
        wmove(stdscr, tx, ty);
        turnedDeck->get_top_card().display(COLOR_WHITE, COLOR_CYAN, tx, ty);
    }

    for (int i = 0; i < 7; i++) {
        tx = 3 + i * (CARD_WIDTH + 2);
        ty = 3 + 2 + CARD_HEIGHT;
        for (int j = 0; j < tableaus[i]->size(); j++) {
            if (j < tableauPositions[i]) {
                Card::display_back(COLOR_RED, COLOR_WHITE, tx, ty);
            }
            else {
                (*tableaus[i])[j].display(COLOR_WHITE, COLOR_BLACK, tx, ty);
            }
            ty += 2;
        }
    }
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