#pragma once

#include "board.hpp"
#include "constants.hpp"

int evaluate(const Board&);

const std::unordered_map<int, int> piece_value_map = {
    {PAWN_W, 100},
    {KNIGHT_W, 300},
    {BISHOP_W, 300},
    {ROOK_W, 500},
    {QUEEN_W, 900},
    {KING_W, 20000},
    {PAWN_B, -100},
    {KNIGHT_B, -300},
    {BISHOP_B, -300},
    {ROOK_B, -500},
    {QUEEN_B, -900},
    {KING_B, -20000},
    {BLANK, 0}
};
