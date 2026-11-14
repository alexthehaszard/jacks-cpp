#include "../GameState.hpp"
#include "tests.hpp"

namespace constexpr_tests::test_cases {
constexpr void FindsPair() {
  constexpr DeckOfCards one_pair{{1, 2, 9, 3}};
  constexpr GameState game(one_pair);

  constexpr auto pair = game.find_pair();
  static_assert(pair.has_value());
  // returns index 1 and 2 (pair 2+9=11)
  static_assert(pair.value() == std::array<size_t, 2>{1, 2});
}

constexpr void FindsNoPair() {
  constexpr DeckOfCards no_pair{{1, 2, 3, 4}};
  constexpr GameState game(no_pair);

  constexpr auto pair = game.find_pair();
  // no pair in this board
  static_assert(!pair.has_value());
}

constexpr void FindsTriple() {
  constexpr DeckOfCards one_triple{{1, 11, 12, 13}};
  constexpr GameState game(one_triple);

  constexpr auto triple = game.find_triple();
  static_assert(triple.has_value());
  // return index 1, 2 and 3 (triple jack+queen+king)
  static_assert(triple.value() == std::array<size_t, 3>{1, 2, 3});
}

constexpr void FindsNoTriple() {
  constexpr DeckOfCards no_triple{{1, 2, 3, 4}};
  constexpr GameState game(no_triple);

  constexpr auto triple = game.find_triple();
  // no triple in this board
  static_assert(!triple.has_value());
}
} // namespace constexpr_tests::test_cases

namespace constexpr_tests {
consteval void Test_GameState() {
  constexpr_tests::test_cases::FindsPair();
  constexpr_tests::test_cases::FindsNoPair();
  constexpr_tests::test_cases::FindsTriple();
  constexpr_tests::test_cases::FindsNoTriple();
}
} // namespace constexpr_tests
