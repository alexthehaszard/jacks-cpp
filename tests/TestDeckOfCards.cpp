#include "../DeckOfCards.hpp"
#include "tests.hpp"

#include <algorithm>
#include <ostream>
#include <print>

/// Makes a copy of a deck, stored in a vector
/// The resulting vector will contain the cards in the
/// order that they are pop'd out of the deck.
std::vector<Card> CopyAllCardsFromDeck(DeckOfCards deck) {
  std::vector<Card> result;
  while (const auto card = deck.try_pop_card()) {
    result.push_back(*card);
  }
  return result;
}

namespace tests::test_cases {
void FreshAndShuffledDeckDiffer(DeckOfCards &fresh_deck,
                                DeckOfCards &shuffled_deck) {
  const auto ripped_fresh_deck = CopyAllCardsFromDeck(fresh_deck);
  const auto ripped_shuffled_deck = CopyAllCardsFromDeck(shuffled_deck);

  AssertTrue(ripped_fresh_deck != ripped_shuffled_deck,
             "FAILED: shuffled deck is the same as a fresh deck");
  std::println("PASSED: fresh deck is different to shuffled deck");
}

void DeckContainsCorrectNumberOfCards(DeckOfCards &deck,
                                      std::string_view name) {
  const auto ripped_deck = CopyAllCardsFromDeck(deck);
  const std::array<std::uint8_t, 13> cards{1, 2, 3,  4,  5,  6, 7,
                                           8, 9, 10, 11, 12, 13};
  for (const auto &card : cards) {
    AssertTrue(std::count(ripped_deck.begin(), ripped_deck.end(), card) == 4,
               std::format("FAILED: {} deck has incorrect number of card {}",
                           name, card)
                   .c_str());
    std::println("PASSED: {} deck has the correct number of {}'s", name, card);
  }
}
} // namespace tests::test_cases

void tests::Test_DeckOfCards() {
  DeckOfCards fresh_deck{};
  DeckOfCards shuffled_deck{};
  shuffled_deck.shuffle();

  tests::test_cases::FreshAndShuffledDeckDiffer(fresh_deck, shuffled_deck);
  tests::test_cases::DeckContainsCorrectNumberOfCards(fresh_deck, "fresh");
  tests::test_cases::DeckContainsCorrectNumberOfCards(shuffled_deck,
                                                      "shuffled");
}
