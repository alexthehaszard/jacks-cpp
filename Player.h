#pragma once

#include "GameState.h"

enum class GameResult { Won, Lost };

namespace player {
GameResult PlayNewGame() {
  DeckOfCards deck;
  deck.shuffle();

  GameState game{std::move(deck)};
  while (true) {
    auto pair = game.find_pair();
    if (pair) {
      if (!game.replace((*pair)[0]) || !game.replace((*pair)[1]))
        break;
    }

    auto triple = game.find_triple();
    if (triple) {
      if (!game.replace((*triple)[0]) || !game.replace((*triple)[1]) ||
          !game.replace((*triple)[2]))
        break;
    } else if (!pair) {
      // no pair or triple :(
      break;
    }
  }
  return game.has_won() ? GameResult::Won : GameResult::Lost;
}
} // namespace player