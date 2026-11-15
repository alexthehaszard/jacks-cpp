#pragma once

#include "Card.hpp"

#include <array>
#include <format>
#include <random>

/// Stores a deck of cards. Acts like a "stack", where you can pop
/// off the top card from the deck.
///
/// Everything here is constexpr!
/// Except for shuffling a deck. We can't do that at compile time.
/// If you want a "shuffled" deck at compile time, you must define
/// the exact "shuffled" state of that deck, and pass it into the
/// constructor.
class DeckOfCards {
  static constexpr std::uint8_t number_of_cards = 52;
  static constexpr std::array<Card, number_of_cards> standard_deck = {
      1,  2,  3,  4, 5,  6,  7,  8,  9, 10, 11, 12, 13, 1,  2,  3, 4, 5,
      6,  7,  8,  9, 10, 11, 12, 13, 1, 2,  3,  4,  5,  6,  7,  8, 9, 10,
      11, 12, 13, 1, 2,  3,  4,  5,  6, 7,  8,  9,  10, 11, 12, 13};

  using Deck = std::array<Card, number_of_cards>;

  size_t deck_pointer_{0};
  Deck deck_{standard_deck};

public:
  constexpr DeckOfCards() = default;
  explicit constexpr DeckOfCards(const Deck &other) : deck_{other} {};

  void shuffle() {
    if (deck_pointer_ != 0) {
      throw std::runtime_error(
          "Should not shuffle a deck after it has been used");
    }

    static std::random_device device;
    static std::minstd_rand prng{device()};
    static std::uniform_int_distribution distribution{0UZ, deck_.size() - 1};

    for (auto &card : deck_) {
      // get the new index (in deck) where this card now belongs
      const auto new_index = distribution(prng);

      // swap the two cards
      const auto temp_card_value = card;
      card = deck_.at(new_index);
      deck_.at(new_index) = temp_card_value;
    }
  }

  constexpr bool has_any_cards_left() const {
    return deck_pointer_ < deck_.size();
  }

  constexpr std::string str() const {
    std::string out{};
    for (const auto &card : deck_) {
      out += std::format("{} ", card_utils::to_string(card));
    }
    return out;
  }

  constexpr std::optional<Card> try_pop_card() {
    if (!has_any_cards_left()) {
      return std::nullopt;
    }

    auto top_card = deck_.at(deck_pointer_);
    deck_pointer_++;
    return top_card;
  }
};