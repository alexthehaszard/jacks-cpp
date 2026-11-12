#include "DeckOfCards.h"
#include "GameState.h"

#include <ostream>

int main()
{
    DeckOfCards deck;
    std::println("{}", deck.str());
    deck.shuffle();
    std::println("{}", deck.str());
    
    GameState game{std::move(deck)};
    std::println("{}\n", game.str());
    game.replace(0);
    std::println("{}\n", game.str());
    game.replace(8);
    std::println("{}\n", game.str());
    return 0;
}