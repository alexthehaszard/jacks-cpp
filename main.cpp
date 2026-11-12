#include "Player.h"

#include <ostream>
#include <chrono>

constexpr size_t games = 10'000'000;

int main()
{
    const auto before = std::chrono::high_resolution_clock::now();

    size_t wins = 0;
    for (size_t i{0}; i < games; i++)
    {
        GameResult result = player::PlayNewGame();
        if (result == GameResult::Won) wins++;
    }
    const auto after = std::chrono::high_resolution_clock::now(); 
    const auto duration = after - before;

    std::println("You won {}/{} games in {}", wins, games, std::chrono::duration_cast<std::chrono::milliseconds>(duration));
    return 0;
}