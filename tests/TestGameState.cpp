#include "../GameState.hpp"
#include "tests.hpp"

#include "cassert"
#include <print>

constexpr DeckOfCards winning_deck{{1, 10, 2, 9, 3, 8, 4, 7, 5, 6, 11, 12, 13,
                                    1, 10, 2, 9, 3, 8, 4, 7, 5, 6, 11, 12, 13,
                                    1, 10, 2, 9, 3, 8, 4, 7, 5, 6, 11, 12, 13,
                                    1, 10, 2, 9, 3, 8, 4, 7, 5, 6, 11, 12, 13}};

// invalid deck, but who cares?
constexpr DeckOfCards losing_deck{{1, 1, 1, 1, 2, 2, 2, 2, 3, 3,  3,  3,  4,
                                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}};

void PlayGame(GameState &game) {
  while (true) {
    auto pair = game.find_pair();
    if (pair) {
      if (!game.replace((*pair).at(0)) || !game.replace((*pair).at(1))) {
        break;
      }
    }

    auto triple = game.find_triple();
    if (triple) {
      if (!game.replace((*triple).at(0)) || !game.replace((*triple).at(1)) ||
          !game.replace((*triple).at(2))) {
        break;
      }
    } else if (!pair) {
      break;
    }
  }
}

namespace tests::test_cases {
void WinsGame() {
  GameState game(winning_deck);
  PlayGame(game);
  assert(game.has_won() &&
         "FAILED: the game was supposed to have been won, but was lost");
  std::println("PASSED: The game was successfully won");
}

void LosesGame() {
  GameState game(losing_deck);
  PlayGame(game);
  assert(!game.has_won() &&
         "FAILED: the game was supposed to have been lost, but was won");
  std::println("PASSED: the game was successfully lost");
}
} // namespace tests::test_cases

void tests::Test_GameState() {
  tests::test_cases::WinsGame();
  tests::test_cases::LosesGame();
}