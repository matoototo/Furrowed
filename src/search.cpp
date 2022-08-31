#include "board.hpp"
#include "search.hpp"

#include <stack>
#include <queue>
#include <iostream>
#include <algorithm>

void BFS(const Board& start, int depth) {
    int count = 0;
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
            new_board.make_move(move);
            queue.push(new_board);
        }
    }
    std::cout << "Visited " << count << " boards" << std::endl;
}

void DFS(const Board& start, int depth) {
    int count = 0;
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
            new_board.make_move(move);
            stack.push(new_board);
        }
    }
    std::cout << "Visited " << count << " boards" << std::endl;
}
