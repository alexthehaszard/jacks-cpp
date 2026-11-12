#include "DeckOfCards.h"
#include "GameState.h"

#include <ostream>
#include <chrono>

int main()
{
    const auto before = std::chrono::high_resolution_clock::now();

    DeckOfCards deck;
    deck.shuffle();
    
    GameState game{std::move(deck)};
    while (true)
    {
        auto pair = game.find_pair();
        if (pair)
        {
            // std::println("swapping pair {} {}", (*pair)[0], (*pair)[1]);
            // std::println("board: \n{}\n", game.str());
            // if any of our replaces fail, break out of the loop.
            if (!game.replace((*pair)[0]) || 
                !game.replace((*pair)[1])) 
                break;
        }

        auto triple = game.find_triple();
        if (triple)
        {
            if (!game.replace((*triple)[0]) || 
                !game.replace((*triple)[1]) || 
                !game.replace((*triple)[2])) 
                break;
        }
        else if (!pair) 
        {
            // no pair or triple :(
            break;
        }
    }

    const auto after = std::chrono::high_resolution_clock::now(); 
    const auto duration = after - before;

    if (game.has_won())
    {
        std::println("You won! Sim time {}", duration);
    }
    else
    {
        std::println("You lose. :( Sim time {}", duration);
        std::println("Final board: \n{}", game.str());
    }

    return 0;
}