#pragma once

#include "Card.hpp"
#include "DeckOfCards.hpp"

#include <algorithm>
#include <ostream>

/// Stores the state of the game.
/// Also provides very specific ways to interact with that state (modifying
/// and accessing).
///
/// All constexpr, except "replace".
class GameState {
  constexpr static size_t board_size = 9;

  DeckOfCards cards_;
  // maybe make board_ an unordered_map, where each key is the card, and the
  // value is the number of that card on the board
  std::array<Card, board_size> board_{};

public:
  constexpr explicit GameState(DeckOfCards cards) : cards_(cards) {
    // take the first `board_size` cards from the top of the deck
    for (size_t index{0}; index < board_size; index++) {
      auto top_card = cards_.try_pop_card();
      if (top_card == std::nullopt) {
        throw std::runtime_error("Could not initialize board");
      }

      board_.at(index) = *top_card;
    }
  }

  constexpr std::string str() {
    constexpr size_t row_length = 3;

    std::string result;
    for (size_t card_index{0}; card_index < board_size; card_index++) {
      if (card_index > 0 && card_index % row_length == 0) {
        result += "\n";
      }
      result +=
          std::format("{} ", card_utils::to_string(board_.at(card_index)));
    }
    return result;
  }

  /// returns true if the value was replaced
  /// returns false if we ran out of cards
  /// if you provided an invalid index, we will throw a tantrum
  constexpr bool replace(const size_t index) {
    if (index >= board_size) {
      throw std::invalid_argument("index out of range");
    }
    const auto top_card = cards_.try_pop_card();

    if (top_card == std::nullopt) {
      return false;
    }

    board_.at(index) = top_card.value();
    return true;
  }

  constexpr bool has_won() { return !cards_.has_any_cards_left(); }

  constexpr std::optional<std::array<size_t, 3>> search() const {
    constexpr std::uint8_t sums_to = 11;
    bool have_we_looked_for_face = false;
    for (auto i{0uz}; i < board_.size(); i++) {
      for (auto j{i + 1}; j < board_.size(); j++) {
        if (board_[i] + board_[j] == sums_to)
          return std::array<size_t, 3>{i, j, 0xFFFF};
        if (!have_we_looked_for_face && board_[i] > 10 && board_[j] > 10 &&
            board_[i] != board_[j]) {
          have_we_looked_for_face = true;
          auto sum = board_[i] + board_[j];
          for (auto k{j + 1}; k < board_.size(); k++) {
            if (sum + board_[k] == 36) {
              return std::array<size_t, 3>{i, j, k};
            }
          }
        }
      }
    }
    return std::nullopt;
  }

  // /// finds a pair of indexes where the values add to 11
  // /// if none exist, return nullopt
  // constexpr std::optional<std::array<size_t, 2>> find_pair() const {
  //   for (std::uint8_t i{1}; i <= sums_to / 2; i++) {
  //     const auto *const first_it = std::find(board_.begin(), board_.end(),
  //     i); if (first_it == board_.end()) {
  //       continue;
  //     }
  //     const auto *const second_it =
  //         std::find(board_.begin(), board_.end(), sums_to - i);
  //     if (second_it == board_.end()) {
  //       continue;
  //     }

  //     return std::array<size_t, 2>{
  //         static_cast<size_t>(first_it - board_.begin()),
  //         static_cast<size_t>(second_it - board_.begin())};
  //   }
  //   return std::nullopt;
  // }

  // /// finds a trio of indexes where the values are king, queen, jack
  // /// if none exist, return nullopt
  // constexpr std::optional<std::array<size_t, 3>> find_triple() const {
  //   std::array<size_t, card_utils::face_cards.size()> result_indexes{};
  //   for (size_t i{0}; i < card_utils::face_cards.size(); i++) {
  //     const auto *const face_it =
  //         std::find(board_.begin(), board_.end(),
  //         card_utils::face_cards.at(i));
  //     if (face_it == board_.end()) {
  //       return std::nullopt;
  //     }
  //     result_indexes.at(i) = static_cast<size_t>(face_it - board_.begin());
  //   }
  //   return result_indexes;
  // }
};