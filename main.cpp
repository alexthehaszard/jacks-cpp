#include "Player.h"

#include <ostream>
#include <chrono>
#include <print>
#include <mutex>
#include <thread>

constexpr size_t games = 100'000;
constexpr size_t thread_count = 10;

int main()
{
    const auto before = std::chrono::high_resolution_clock::now();

    std::atomic<size_t> wins = 0;
    std::mutex played_mutex;
    size_t games_played = 0;

    auto thread_function = [&wins, &games_played, &played_mutex]() {
        while (true)
        {
            {
                std::unique_lock lk(played_mutex);
                if (games_played < games) games_played++;
                else break;
            }
            GameResult result = player::PlayNewGame();
            if (result == GameResult::Won) wins++;
        }
    };


    {
        std::array<std::jthread, thread_count> threads{};
        for (auto& thread : threads)
        {
            thread = std::jthread{thread_function};
        }
    }
    const auto after = std::chrono::high_resolution_clock::now(); 
    const auto duration = after - before;

    std::println("You won {}/{} games in {}", wins.load(), games, std::chrono::duration_cast<std::chrono::milliseconds>(duration));
    return 0;
}