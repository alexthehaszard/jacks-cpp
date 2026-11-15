#pragma once

#include "GameState.hpp"

#include <chrono>

enum class GameResult : std::uint8_t { Won, Lost };

namespace player {

using namespace std::chrono_literals;
static std::chrono::duration<double, std::nano> average_shuffle_runtime{0ns};
static std::chrono::duration<double, std::nano> average_game_runtime{0ns};
static size_t game_data_points{0};
static std::chrono::duration<double, std::nano> average_find_runtime{0ns};
static std::chrono::duration<double, std::nano> average_replace_runtime{0ns};
static size_t find_data_points{0};
static size_t replace_data_points{0};

GameResult PlayNewGame() {
  const auto before = std::chrono::high_resolution_clock::now();
  DeckOfCards deck;
  deck.shuffle();

  const auto after_shuffle = std::chrono::high_resolution_clock::now();

  GameState game{deck};
  while (true) {
    const auto before_find = std::chrono::high_resolution_clock::now();
    auto pair = game.find_pair();
    const auto after_find = std::chrono::high_resolution_clock::now();
    if (pair) {
      if (!game.replace((*pair).at(0)) || !game.replace((*pair).at(1))) {
        break;
      }
      const auto after_replace = std::chrono::high_resolution_clock::now();

      std::chrono::nanoseconds replace_time = after_replace - after_find;
      replace_data_points++;
      double ratio = 1.0 / replace_data_points;
      average_replace_runtime *= 1 - ratio;
      average_replace_runtime += replace_time * ratio;
    }
    std::chrono::nanoseconds find_time = after_find - before_find;
    find_data_points++;
    double ratio = 1.0 / find_data_points;
    average_find_runtime *= 1 - ratio;
    average_find_runtime += find_time * ratio;

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
  const auto after_game = std::chrono::high_resolution_clock::now();

  std::chrono::nanoseconds shuffle_time = after_shuffle - before;
  std::chrono::nanoseconds game_time = after_game - after_shuffle;
  game_data_points++;

  double ratio = 1.0 / game_data_points;
  average_shuffle_runtime *= 1 - ratio;
  average_shuffle_runtime += shuffle_time * ratio;
  average_game_runtime *= 1 - ratio;
  average_game_runtime += game_time * ratio;

  return game.has_won() ? GameResult::Won : GameResult::Lost;
}
} // namespace player