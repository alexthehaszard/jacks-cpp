#include "tests.h"

#include <ostream>

int main()
{
    std::println("-- Tests: Deck Of Cards --");
    tests::Test_DeckOfCards();
    std::println("-- Tests: Game State --");
    tests::Test_GameState();
    return 0;
}