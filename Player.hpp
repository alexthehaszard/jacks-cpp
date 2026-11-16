#pragma once

#include "GameState.hpp"

enum class GameResult : std::uint8_t { Won, Lost };

namespace player {
GameResult PlayNewGame() {
  DeckOfCards deck;
  deck.shuffle();

  GameState game{deck};
  while (true) {
    auto result = game.search();
    if (result) {
      if (!game.replace((*result).at(0)) || !game.replace((*result).at(1)) ||
          (result.value().at(2) != 0xFFFF && !game.replace((*result).at(2)))) {
        break;
      }
    } else {
      break;
    }
  }
  return game.has_won() ? GameResult::Won : GameResult::Lost;
}
} // namespace player