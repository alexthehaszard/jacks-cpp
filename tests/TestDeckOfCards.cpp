#include "../DeckOfCards.hpp"
#include "tests.hpp"

#include <algorithm>
#include <cassert>
#include <ostream>
#include <print>

namespace tests::test_cases {
void FreshAndShuffledDeckDiffer(DeckOfCards &fresh_deck,
                                DeckOfCards &shuffled_deck) {
  assert(!std::equal(fresh_deck.deck.begin(), fresh_deck.deck.end(),
                     shuffled_deck.deck.begin(), shuffled_deck.deck.end()) &&
         "FAILED: shuffled deck is the same as a fresh deck");
  std::println("PASSED: fresh deck is different to shuffled deck");
}

void DeckContainsCorrectNumberOfCards(DeckOfCards &deck,
                                      std::string_view name) {
  const std::array<std::uint8_t, 13> cards{1, 2, 3,  4,  5,  6, 7,
                                           8, 9, 10, 11, 12, 13};
  for (const auto &card : cards) {
    assert(std::count(deck.deck.begin(), deck.deck.end(), card) == 4 &&
           std::format("FAILED: {} deck has incorrect number of a card", name)
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
