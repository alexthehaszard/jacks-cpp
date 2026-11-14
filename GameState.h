#pragma once

#include "Card.h"
#include "DeckOfCards.h"

#include <algorithm>
#include <ostream>

class GameState {
  constexpr static size_t board_size = 9;

  DeckOfCards cards_;
  // maybe make board_ an unordered_map, where each key is the card, and the
  // value is the number of that card on the board
  std::array<Card, board_size> board_;

public:
  constexpr explicit GameState(DeckOfCards cards)
      : cards_(std::move(cards)), board_{} {
    // take the first `board_size` cards from the top of the deck
    for (size_t index{0}; index < board_size; index++) {
      auto top_card = cards_.try_pop_card();
      if (top_card == std::nullopt)
        throw std::runtime_error("Could not initialize board");

      board_[index] = std::move(*top_card);
    }
  }

  constexpr std::string str() {
    constexpr size_t row_length = 3;

    std::string result{""};
    for (size_t card_index{0}; card_index < board_size; card_index++) {
      if (card_index > 0 && card_index % row_length == 0) {
        result += "\n";
      }
      result += std::format("{} ", board_[card_index].str());
    }
    return result;
  }

  /// returns true if the value was replaced
  /// returns false if we ran out of cards
  /// if you provided an invalid index, we will throw a tantrum
  constexpr bool replace(const size_t index) {
    if (index >= board_size)
      throw std::invalid_argument("index out of range");
    const auto top_card = cards_.try_pop_card();

    if (top_card == std::nullopt)
      return false;

    board_[index] = std::move(*top_card);
    return true;
  }

  constexpr bool has_won() { return !cards_.has_any_cards_left(); }

  /// finds a pair of indexes where the values add to 11
  /// if none exist, return nullopt
  constexpr std::optional<std::array<size_t, 2>> find_pair() {
    constexpr uint8_t sums_to = 11;
    for (uint8_t i{1}; i <= sums_to / 2; i++) {
      const auto first_it = std::find(board_.begin(), board_.end(), i);
      if (first_it == board_.end())
        continue;
      const auto second_it =
          std::find(board_.begin(), board_.end(), sums_to - i);
      if (second_it == board_.end())
        continue;

      return std::array<size_t, 2>{
          static_cast<size_t>(first_it - board_.begin()),
          static_cast<size_t>(second_it - board_.begin())};
    }
    return std::nullopt;
  }

  /// finds a trio of indexes where the values are king, queen, jack
  /// if none exist, return nullopt
  constexpr std::optional<std::array<size_t, 3>> find_triple() {
    constexpr std::array<Card, 3> face_cards{11, 12, 13};
    std::array<size_t, 3> result_indexes{};
    for (size_t i{0}; i < 3; i++) {
      const auto it = std::find(board_.begin(), board_.end(), face_cards[i]);
      if (it == board_.end())
        return std::nullopt;
      result_indexes[i] = static_cast<size_t>(it - board_.begin());
    }
    return result_indexes;
  }
};