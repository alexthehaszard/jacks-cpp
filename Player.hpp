#pragma once

#include "GameState.hpp"

enum class GameResult : std::uint8_t { Won, Lost };

namespace player {
GameResult PlayNewGame() {
  DeckOfCards deck;
  deck.shuffle();

  GameState game{deck};
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
      // no pair or triple :(
      break;
    }
  }
  return game.has_won() ? GameResult::Won : GameResult::Lost;
}
} // namespace player