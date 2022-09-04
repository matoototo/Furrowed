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

void BFS(const Board& start, int depth) {
    long long count = 0;
    std::queue<Board> queue;
    queue.push(start);
    int starting_ply_number = start.ply_number;
    while (!queue.empty()) {
        Board board = queue.front();
        queue.pop();
        if (board.ply_number - starting_ply_number >= depth) {
            break;
        }
        for (const auto& move : board.legal_moves()) {
            if (board.ply_number - starting_ply_number == depth - 1) {
                count++;
            }
            Board new_board = board;
            new_board.make_move(move, true);
            queue.push(new_board);
        }
    }
    std::cout << captures << " " << en_passants << " " << castles << " " << promotions << std::endl;
    std::cout << "Visited " << count << " boards" << std::endl;
}

void DFS(const Board& start, int depth) {
    long long count = 0;
    std::stack<Board> stack;
    stack.push(start);
    int starting_ply_number = start.ply_number;
    while (!stack.empty()) {
        Board board = stack.top();
        stack.pop();
        if (board.ply_number - starting_ply_number >= depth) {
            continue;
        }
        for (const auto& move : board.legal_moves()) {
            if (board.ply_number - starting_ply_number == depth - 1) {
                count++;
            }
            Board new_board = board;
            new_board.make_move(move, true);
            stack.push(new_board);
        }
    }
    std::cout << captures << " " << en_passants << " " << castles << " " << promotions << std::endl;
    std::cout << "Visited " << count << " boards" << std::endl;
}

std::pair<int, Move> negamax(const Board& board, int depth, std::atomic<bool>& stop, long long think_until) {
    if (depth == 0 || stop || now() > think_until) {
        return {evaluate(board), Move()};
    }
    int best_value = -1000000;
    Move best_move;
    auto moves = board.legal_moves();
    if (moves.size() == 0) return {0, Move()};
    for (const auto& move : moves) {
        Board new_board = board;
        new_board.make_move(move);
        int value = -negamax(new_board, depth - 1, stop, think_until).first;
        if (value > best_value || best_value == -1000000) {
            best_value = value;
            best_move = move;
        }
    }
    return {best_value, best_move};
}

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

std::pair<int, Move> alpha_beta(const Board& board, int depth, int alpha, int beta, std::atomic<bool>& stop, long long think_until) {
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
    if (moves.size() == 0) {
        if (board.is_in_check(board.find_king()))
            return {-1000000, Move()};
        return {0, Move()};
    }
    for (const auto& move : moves) {
        Board new_board = board;
        new_board.make_move(move);
        int value = -alpha_beta(new_board, depth - 1, -beta, -alpha, stop, think_until).first;
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
    return {best_value, best_move};
}
