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

    std::println(
        "Average shuffle time: {}\nAverage game time: {}\nDatapoints: {}",
        player::average_shuffle_runtime, player::average_game_runtime,
        player::game_data_points);
    std::println(
        "Average find time: {}\nAverage replace time: {}\nFind datapoints: {}\nReplace Datapoints: {}",
        player::average_find_runtime, player::average_replace_runtime,
        player::find_data_points, player::replace_data_points);

    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Exception caught in function main: {}" << e.what() << '\n';
    return 1;
  }
}