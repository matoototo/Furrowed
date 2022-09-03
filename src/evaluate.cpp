#include "move.hpp"
#include "evaluate.hpp"

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
    return sign * eval;
}
