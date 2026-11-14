#pragma once

#include <stdint.h>
#include <string>

/// In jacks, we don't care about the suit of a card.
/// So, we don't implement it. We just have the value of that card.
struct Card {
  /// number from 1 - 13
  /// 1 = ace
  /// 2 = 2
  /// ...
  /// 10 = 10
  /// 11 = jack
  /// 12 = queen
  /// 13 = king
  uint8_t value;

  constexpr bool operator==(const unsigned char &other) {
    return value == other;
  }
  constexpr bool operator==(const Card &other) const {
    return value == other.value;
  }

  constexpr std::string str() {
    if (value == 11)
      return "j";
    else if (value == 12)
      return "q";
    else if (value == 13)
      return "k";
    else
      return std::to_string(value);
  }

  constexpr static uint8_t min = 1;
  constexpr static uint8_t max = 13;
};