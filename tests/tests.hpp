#pragma once

#include <print>
#include <string>

void AssertTrue(bool statement, std::string_view message);

namespace tests {
void Test_DeckOfCards();
void Test_GameState();
} // namespace tests