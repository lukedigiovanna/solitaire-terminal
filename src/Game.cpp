#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() : currCard(0) {
    // for (int i = 0; i < 4; i++) piles[i] = 0;


    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j--;) {
            // deck.pop_back();
            // tableaus[i].push_back(*deck.end());
        }
        tableauPositions[i] = i;
    }
}

void Game::display() const {
    
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