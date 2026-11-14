#include "Player.hpp"

#include <chrono>
#include <iostream>
#include <print>

constexpr size_t games = 100'000;

int main() {
  try {
    const auto before = std::chrono::high_resolution_clock::now();

    size_t wins = 0;
    for (size_t i{0}; i < games; i++) {
      GameResult result = player::PlayNewGame();
      if (result == GameResult::Won) {
        wins++;
      }
    }
    const auto after = std::chrono::high_resolution_clock::now();
    const auto duration = after - before;

    std::println(
        "You won {}/{} games in {}", wins, games,
        std::chrono::duration_cast<std::chrono::milliseconds>(duration));

    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Exception caught in function main: {}" << e.what() << '\n';
    return 1;
  }
}