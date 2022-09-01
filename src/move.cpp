#include "move.hpp"
#include "board.hpp"
#include "constants.hpp"

#include <iostream>

Move Move::from_str(std::string s, Board& board) {
    Move move;
    int sign = board.is_white ? -1 : 1;
    move.from = square_map.at(std::string{s[0], s[1]});
    move.to = square_map.at(std::string{s[2], s[3]});
    if (s.size() > 4) {
        move.promotion = piece_map.at(s[4]) * sign;
    }
    if (move.from == E1 && move.to == G1 && board.board[E1] == KING_W) {
        move.castling = CASTLE_KW;
    } else if (move.from == E1 && move.to == C1 && board.board[E1] == KING_W) {
        move.castling = CASTLE_QW;
    } else if (move.from == E8 && move.to == G8 && board.board[E8] == KING_B) {
        move.castling = CASTLE_KB;
    } else if (move.from == E8 && move.to == C8 && board.board[E8] == KING_B) {
        move.castling = CASTLE_QB;
    }
    return move;
}

std::string Move::to_str() const {
    std::string str;
    // if (castling) {
    //     if (castling == CASTLE_KW || castling == CASTLE_KB) {
    //         str = "O-O";
    //     } else {
    //         str = "O-O-O";
    //     }
    // } else {
    if (promotion) {
        str = index_to_coord(from) + index_to_coord(to) + (char)tolower(piece_str_map.at(promotion));
    } else {
        str = index_to_coord(from) + index_to_coord(to);
    }
    return str;
}
