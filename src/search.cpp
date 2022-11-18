#include "time.hpp"
#include "board.hpp"
#include "search.hpp"
#include "evaluate.hpp"

#include <stack>
#include <queue>
#include <chrono>
#include <atomic>
#include <utility>
#include <iostream>
#include <algorithm>


int Quiesce(const Board& board, int alpha, int beta, long long think_until) {
    if (now() > think_until) return beta; // abort
    int stand_pat = evaluate(board);
    if (stand_pat >= beta) return beta;
    if (stand_pat > alpha) alpha = stand_pat;
    for (const auto& move : board.forcing_moves()) {
        Board new_board = board;
        new_board.make_move(move);
        int score = -Quiesce(new_board, -beta, -alpha, think_until);
        if (score >= beta) return beta;
        if (score > alpha) alpha = score;
    }
    return alpha;
}

std::function<bool(const Move&, const Move&)> move_order(const Board& board) {
    return [&board](const Move& a, const Move& b) {
        if (is_capture(board, a) && !is_capture(board, b)) return true;
        // if (is_check(board, a) && !is_check(board, b)) return true; TODO: segfault
        return false;
    };
}

std::pair<int, Move> alpha_beta(Engine& engine, const Board& board, int depth, int alpha, int beta, std::atomic<bool>& stop, long long think_until) {
    if (depth == 0 || stop || now() > think_until) {
        if (depth == 0) {
            auto q_value = Quiesce(board, alpha, beta, think_until);
            return {q_value, Move()};
        } else {
            return {beta, Move()};
        }
    }

    int best_value = -1000000;
    Move best_move;

    auto moves = board.legal_moves();
    std::sort(moves.begin(), moves.end(), move_order(board));

    if (moves.size() == 0) {
        if (board.is_in_check(board.find_king()))
            return {-1000000, Move()};
        return {0, Move()};
    }

    auto probing_result = engine.table.probe(board);
    if (probing_result.second && std::find(moves.begin(), moves.end(), probing_result.first.best) != moves.end()) {
        // this doesn't work for some reason, causes very silly moves
        // if (probing_result.first.depth >= depth && probing_result.first.value < beta && probing_result.first.value >= alpha) {
        //     return {probing_result.first.value, probing_result.first.best};
        // } else {
        best_move = probing_result.first.best;
        // somehow avoid duplicating code? I'm not sure how
        Board new_board = board;
        new_board.make_move(probing_result.first.best, false, &engine.table);
        ++engine.nodes;
        best_value = -alpha_beta(engine, new_board, depth - 1, -beta, -alpha, stop, think_until).first;
        if (best_value > alpha) {
            alpha = best_value;
        }
        if (alpha >= beta || alpha == 1000000) {
            engine.table.add(board, best_move, best_value, depth, 1);
            return {best_value, best_move};
        }
        // }
    }

    for (const auto& move : moves) {
        if (probing_result.second && move == probing_result.first.best) continue;
        Board new_board = board;
        new_board.make_move(move, false, &engine.table);
        ++engine.nodes;
        int value = -alpha_beta(engine, new_board, depth - 1, -beta, -alpha, stop, think_until).first;
        if (value > best_value || best_value == -1000000) {
            best_value = value;
            best_move = move;
        }
        if (best_value > alpha) {
            alpha = best_value;
        }
        if (alpha >= beta) {
            break;
        }
        if (alpha == 1000000) {
            break;
        }
    }
    engine.table.add(board, best_move, best_value, depth, 1);
    return {best_value, best_move};
}
