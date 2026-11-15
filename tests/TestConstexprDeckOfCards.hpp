#include "../DeckOfCards.hpp"

/// Does not modify the deck that is passed in!
/// Returns the card that was popped (an optional), and the mutated deck.
consteval std::pair<std::optional<Card>, DeckOfCards>
TryPopFromDeck(DeckOfCards deck) {
  return {deck.try_pop_card(), deck};
}

/// Pops "cards_to_rip" number of cards from the deck, and returns the resulting
/// deck.
consteval DeckOfCards RipCardsOutOfDeck(DeckOfCards deck, size_t cards_to_rip) {
  for (size_t i{0}; i < cards_to_rip; i++) {
    deck.try_pop_card();
  }
  return deck;
}

namespace constexpr_tests::test_cases {
consteval void TryPopCard() {
  constexpr DeckOfCards fresh_deck{{1, 2}};

  // cannot use structured bindings here, they are not constexpr :(
  constexpr auto first_popped_deck = TryPopFromDeck(fresh_deck);
  constexpr auto second_popped_deck = TryPopFromDeck(first_popped_deck.second);

  static_assert(first_popped_deck.first.has_value());
  static_assert(second_popped_deck.first.has_value());
  static_assert(first_popped_deck.first.value() == 1);
  static_assert(second_popped_deck.first.value() == 2);
}

consteval void TryPopCardWithoutAnyCardsLeft() {
  constexpr DeckOfCards standard_deck;

  // once we've popped 52 cards from the deck, try and pop one more.
  constexpr auto flushed_deck = RipCardsOutOfDeck(standard_deck, 52);
  constexpr auto popped_deck = TryPopFromDeck(flushed_deck);

  static_assert(!popped_deck.first.has_value());
}

consteval void HasAnyCardsLeft() {
  constexpr DeckOfCards standard_deck;

  constexpr auto flushed_deck = RipCardsOutOfDeck(standard_deck, 51);
  static_assert(flushed_deck.has_any_cards_left());

  constexpr auto popped_deck = TryPopFromDeck(flushed_deck);
  static_assert(!popped_deck.second.has_any_cards_left());
}
} // namespace constexpr_tests::test_cases

namespace constexpr_tests {
consteval void Test_DeckOfCards() {
  constexpr_tests::test_cases::TryPopCard();
  constexpr_tests::test_cases::TryPopCardWithoutAnyCardsLeft();
  constexpr_tests::test_cases::HasAnyCardsLeft();
}
} // namespace constexpr_tests
