#pragma once

#include "Card.h"
#include "DeckOfCards.h"

#include <ostream>

class GameState
{
    constexpr static size_t board_size = 9;

    DeckOfCards cards_;
    std::array<Card, board_size> board_;
public:
    constexpr explicit GameState(DeckOfCards cards) : cards_(std::move(cards)), board_{}
    {
        // take the first `board_size` cards from the top of the deck
        for (size_t index{0}; index < board_size; index++)
        {
            auto top_card = cards_.try_pop_card();
            if (top_card == std::nullopt) throw std::runtime_error("Could not initialize board");

            board_[index] = std::move(*top_card);
        }
    }

    constexpr std::string str()
    {
        constexpr size_t row_length = 3;

        std::string result{""};
        for (size_t card_index{0}; card_index < board_size; card_index++)
        {
            if (card_index > 0 && card_index % row_length == 0) 
            {
                result += "\n";
            }
            result += std::format("{} ", board_[card_index].str());
        }
        return result;
    }

    constexpr void replace(const size_t index)
    {
        if (index >= board_size) throw std::invalid_argument("index out of range");
        const auto top_card = cards_.try_pop_card();
        if (top_card == std::nullopt) throw std::runtime_error("no more cards");
        board_[index] = std::move(*top_card);
    }

    constexpr bool has_won()
    {
        return cards_.has_any_cards_left();
    }
};