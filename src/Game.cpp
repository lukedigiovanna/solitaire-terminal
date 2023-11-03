#include "Game.h"
#include <iostream>
#include <ncursesw/curses.h>

using namespace std;

Game::Game() : currCard(0) {
    // for (int i = 0; i < 4; i++) piles[i] = 0;
    deck = std::make_unique<StandardDeck>();
    deck->shuffle();
    
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
    for (int i = 0; i < 7; i++) {
        int tx = 3 + i * (CARD_WIDTH + 2);
        int ty = 3;
        for (auto c : *(tableaus[i])) {
            c.display(COLOR_WHITE, COLOR_BLACK, tx, ty++);
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