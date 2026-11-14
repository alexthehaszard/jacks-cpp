#pragma once

#include "Card.hpp"

#include <array>
#include <format>
#include <random>

using Deck = std::array<Card, 52>;

struct DeckOfCards {
  size_t deck_pointer;
  Deck deck;

  constexpr DeckOfCards()
      : deck_pointer{0},
        deck{1,  2,  3,  4, 5,  6,  7,  8,  9, 10, 11, 12, 13, 1,  2,  3, 4, 5,
             6,  7,  8,  9, 10, 11, 12, 13, 1, 2,  3,  4,  5,  6,  7,  8, 9, 10,
             11, 12, 13, 1, 2,  3,  4,  5,  6, 7,  8,  9,  10, 11, 12, 13} {};

  explicit constexpr DeckOfCards(const Deck &other)
      : deck_pointer{0}, deck{other} {};

  constexpr void shuffle() {
    if (deck_pointer != 0)
      throw std::runtime_error(
          "Should not shuffle a deck after it has been used");

    static std::random_device device;
    static std::mt19937 prng{device()};
    static std::uniform_int_distribution distribution{0uz, deck.size() - 1};

    for (auto &card : deck) {
      // get the new index (in deck) where this card now belongs
      const auto new_index = distribution(prng);

      // swap the two cards
      const auto temp_card_value = card.value;
      card.value = deck[new_index].value;
      deck[new_index].value = temp_card_value;
    }
  }

  constexpr bool has_any_cards_left() { return deck_pointer < deck.size(); }

  std::string str() {
    std::string out{};
    for (auto &card : deck) {
      out += std::format("{} ", card.str());
    }
    return out;
  }

  constexpr std::optional<Card> try_pop_card() {
    if (deck_pointer >= deck.size())
      return std::nullopt;

    auto top_card = deck[deck_pointer];
    deck_pointer++;
    return top_card;
  }
};