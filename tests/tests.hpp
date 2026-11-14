#pragma once

#include <print>
#include <string>

inline void AssertTrue(bool statement, std::string_view message) {
  if (!statement) {
    std::println("{}", message);
    throw std::runtime_error("Assertion failed");
  }
}

namespace tests {
void Test_DeckOfCards();
void Test_GameState();
} // namespace tests
