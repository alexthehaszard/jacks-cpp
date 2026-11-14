#include "tests.hpp"

#include <iostream>
#include <print>

int main() {
  try {
    std::println("-- Tests: Deck Of Cards --");
    tests::Test_DeckOfCards();
    std::println("-- Tests: Game State --");
    tests::Test_GameState();
    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Exception caught in function main: {}" << e.what() << '\n';
    return 1;
  }
}