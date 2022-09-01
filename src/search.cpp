#include "board.hpp"
#include "search.hpp"
#include "evaluate.hpp"

#include <stack>
#include <queue>
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

std::pair<int, Move> negamax(const Board& board, int depth, std::atomic<bool>& stop) {
    if (depth == 0 || stop) {
        return {evaluate(board), Move()};
    }
    int best_value = -1000000;
    Move best_move;
    for (const auto& move : board.legal_moves()) {
        Board new_board = board;
        new_board.make_move(move);
        int value = -negamax(new_board, depth - 1, stop).first;
        if (value > best_value) {
            best_value = value;
            best_move = move;
        }
    }
    return {best_value, best_move};
}
