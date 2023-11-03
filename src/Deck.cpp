#include "Deck.h"

#include <random>

Deck::Deck() {
    
}   

void Deck::shuffle() {
    for (int i = 0; i < this->size(); i++) {
        int i1 = rand() % this->size();
        int i2 = rand() % this->size();
        Card temp = this->cards[i1];
        this->cards[i1] = this->cards[i2];
        this->cards[i2] = temp;
    }
}

int Deck::size() const {
    return this->cards.size();
}

Card Deck::get_top_card() {
    return *(this->cards.end() - 1);
}

Card Deck::draw_card_top() {
    Card c = *(this->cards.end() - 1);
    this->cards.pop_back();
    return c;
}

// Card Deck::draw_card_bottom() {
//     Card c = *(this->cards.begin());
//     this->cards.pop_front();
//     return c;
// }

void Deck::add_card_top(Card c) {
    this->cards.push_back(c);
}

// void Deck::add_card_bottom(Card c) {
//     this->cards.push_front(c);
// }

vector<Card>::const_iterator Deck::begin() const {
    return this->cards.begin();
}

vector<Card>::const_iterator Deck::end() const {
    return this->cards.end();
}

const Card& Deck::operator[](size_t index) const {
    // Optional: Check if the index is within the bounds of the vector.
    if (index >= cards.size()) {
        throw std::out_of_range("Index out of range");
    }
    return cards[index];
}

StandardDeck::StandardDeck() {
    std::array suits{Suit::CLUBS, Suit::SPADES, Suit::HEARTS, Suit::DIAMONDS};
    for (auto suit : suits) {
        for (int i = 0; i < 13; i++) {
            Card c = Card(suit, i);
            this->cards.push_back(c);
        }
    }
}
