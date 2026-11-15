#include "../GameState.hpp"

/// Initializes a game with a deck, and immediately replaces the first
/// element on the board.
constexpr GameState MakeGameWithFirstElementReplaced(const DeckOfCards &deck) {
  GameState game(deck);
  game.replace(0);
  return game;
}

namespace constexpr_tests::test_cases {
consteval void FindsPair() {
  constexpr DeckOfCards one_pair{{1, 2, 9, 3}};
  constexpr GameState game(one_pair);

  constexpr auto pair = game.find_pair();
  static_assert(pair.has_value());
  // returns index 1 and 2 (pair 2+9=11)
  static_assert(pair.value() == std::array<size_t, 2>{1, 2});
}

consteval void FindsNoPair() {
  constexpr DeckOfCards no_pair{{1, 2, 3, 4}};
  constexpr GameState game(no_pair);

  constexpr auto pair = game.find_pair();
  // no pair in this board
  static_assert(!pair.has_value());
}

consteval void FindsTriple() {
  constexpr DeckOfCards one_triple{{1, 11, 12, 13}};
  constexpr GameState game(one_triple);

  constexpr auto triple = game.find_triple();
  static_assert(triple.has_value());
  // return index 1, 2 and 3 (triple jack+queen+king)
  static_assert(triple.value() == std::array<size_t, 3>{1, 2, 3});
}

consteval void FindsNoTriple() {
  constexpr DeckOfCards no_triple{{1, 2, 3, 4}};
  constexpr GameState game(no_triple);

  constexpr auto triple = game.find_triple();
  // no triple in this board
  static_assert(!triple.has_value());
}

consteval void DoingReplaceGivesAPair() {
  // Before a replacement, this board will have no pairs
  // After a replacement, this board will have a pair
  constexpr DeckOfCards board_needs_a_pair{{1, 2, 1, 1, 1, 1, 1, 1, 1, 9}};
  constexpr GameState game_before_replacing(board_needs_a_pair);
  constexpr GameState game_after_replacing =
      MakeGameWithFirstElementReplaced(board_needs_a_pair);

  constexpr auto before_replacing = game_before_replacing.find_pair();
  constexpr auto after_replacing = game_after_replacing.find_pair();

  static_assert(!before_replacing.has_value());
  static_assert(after_replacing.has_value());
}
} // namespace constexpr_tests::test_cases

namespace constexpr_tests {
consteval void Test_GameState() {
  constexpr_tests::test_cases::FindsPair();
  constexpr_tests::test_cases::FindsNoPair();
  constexpr_tests::test_cases::FindsTriple();
  constexpr_tests::test_cases::FindsNoTriple();
  constexpr_tests::test_cases::DoingReplaceGivesAPair();
}
} // namespace constexpr_tests
