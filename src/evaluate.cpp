#include "move.hpp"
#include "evaluate.hpp"

int doubled_pawns(const Board& board) {
    int eval = 0;
    for (int file = 1; file < 9; ++file) {
        int w_pawns = 0; int b_pawns = 0;
        for (int rank = 20; rank < 90; rank += 10) {
            if (board.board[rank+file] == 1) w_pawns++;
            else if (board.board[rank+file] == -1) b_pawns++;
        }
        if (w_pawns > 1) eval -= (w_pawns-1)*50;
        if (b_pawns > 1) eval += (b_pawns-1)*50;
    }
    return eval;
}

int king_distance(const Board& board, int current_eval) {
    int sign = board.is_white ? 1 : -1;
    int king_pos = board.find_king(true);
    int king_pos_other = board.find_king(false);
    int king_x = king_pos % 10;
    int king_x_other = king_pos_other % 10;
    int king_y = king_pos / 10;
    int king_y_other = king_pos_other / 10;
    int distance = 0;
    const int MAX_DIST = 14;
    for (int i = 21; i < 99; ++i) {
        if (i % 10 == 9) {
            i += 1;
            continue;
        }
        if (sign*board.board[i] > BLANK) {
            distance -= MAX_DIST;
            distance += (std::abs(king_x - i % 10) + std::abs(king_y - i / 10));
        }
        if (sign*board.board[i] < BLANK) {
            distance += MAX_DIST;
            distance -= (std::abs(king_x_other - i % 10) + std::abs(king_y_other - i / 10));
        }
        if (sign*board.board[i] == KING_W && sign*current_eval > 0) {
            distance -= MAX_DIST;
            distance += (std::abs(king_x - i % 10) + std::abs(king_y - i / 10));
        }
        if (sign*board.board[i] == KING_B && sign*current_eval < 0) {
            distance += MAX_DIST;
            distance -= (std::abs(king_x_other - i % 10) + std::abs(king_y_other - i / 10));
        }
    }
    return sign*distance;
}


int evaluate(const Board& board) {
    int sign = board.is_white ? 1 : -1;
    int eval = 0;
    for (int i = 21; i < 99; ++i) {
        if (i % 10 == 9) {
            i += 1;
            continue;
        }
        int piece = board.board[i];
        if (piece != BLANK) {
            eval += piece_value_map.at(piece);
            eval += placement_value_map.at(piece).at(i);
        }
    }
    eval -= king_distance(board, eval);
    eval += doubled_pawns(board);
    return sign * eval;
}
