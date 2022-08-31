#include "move.hpp"
#include "evaluate.hpp"

int evaluate(const Board& board) {
    int sign = board.is_white ? 1 : -1;
    int eval = 0;
    for (int i = 21; i < 99; ++i) {
        if (i % 10 == 9) {
            i += 1;
            continue;
        }
        eval += piece_value_map.at(board.board[i]);
    }
    return sign * eval;
}
