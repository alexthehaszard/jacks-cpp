#include "DeckOfCards.h"

#include <ostream>
#include <cassert>
#include <algorithm>

void Test_DeckOfCards()
{
    DeckOfCards fresh_deck{};
    DeckOfCards shuffled_deck{};
    shuffled_deck.shuffle();

    assert(
        !std::equal(fresh_deck.deck.begin(), fresh_deck.deck.end(), shuffled_deck.deck.begin(), shuffled_deck.deck.end())
        && "shuffled deck is the same as a fresh deck");

    const std::array<uint8_t,13> cards{1,2,3,4,5,6,7,8,9,10,11,12,13};
    for (const auto& card : cards)
    {
        assert(
            std::count(fresh_deck.deck.begin(), fresh_deck.deck.end(), card) == 4 
            && "fresh deck has incorrect number of a card");
        assert(
            std::count(shuffled_deck.deck.begin(), shuffled_deck.deck.end(), card) == 4 
            && "shuffled deck has incorrect number of a card");
    }
}

int main()
{
    Test_DeckOfCards();
    return 0;
}