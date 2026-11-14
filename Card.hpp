#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <utility>

/// In jacks, we don't care about the suit of a card.
/// So, we don't implement it. We just have the value of that card.
/// number from 1 - 13
/// 1 = ace
/// 2 = 2
/// ...
/// 10 = 10
/// 11 = jack
/// 12 = queen
/// 13 = king
using Card = std::uint8_t;

namespace card_utils {
enum class Faces : Card { Jack = 11, Queen = 12, King = 13 };
constexpr std::array<Card, 3> face_cards{std::to_underlying(Faces::Jack),
                                         std::to_underlying(Faces::Queen),
                                         std::to_underlying(Faces::King)};

constexpr std::string to_string(Card card_to_string) {
  if (card_to_string == std::to_underlying(Faces::Jack)) {
    return "j";
  }
  if (card_to_string == std::to_underlying(Faces::Queen)) {
    return "q";
  }
  if (card_to_string == std::to_underlying(Faces::King)) {
    return "k";
  }
  return std::to_string(card_to_string);
}

constexpr static std::uint8_t min = 1;
constexpr static std::uint8_t max = 13;
} // namespace card_utils
