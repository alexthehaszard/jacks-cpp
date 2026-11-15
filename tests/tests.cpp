#include "tests.hpp"
#include "TestConstexprDeckOfCards.hpp"
#include "TestConstexprGameState.hpp"

#include <iostream>
#include <print>

int main() {
  try {
    std::println("-- Tests: Deck Of Cards --");
    tests::Test_DeckOfCards();
    std::println("-- Tests: Game State --");
    tests::Test_GameState();

    // constexpr tests run at compile time, so a failing test will
    // cause a compilation error.
    // really this _should_ be wrapped in a "consteval" block, but
    // that is a c++26 feature that isn't fully supported yet by
    // my build/lint stack
    constexpr_tests::Test_GameState();
    constexpr_tests::Test_DeckOfCards();

    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Exception caught in function main: " << e.what() << '\n';
    return 1;
  }
}