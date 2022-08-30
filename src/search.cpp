#include "board.hpp"
#include "search.hpp"

#include <queue>
#include <iostream>
#include <algorithm>

void BFS(const Board& start, int depth) {
    std::vector<Board> visited;
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
            Board new_board = board;
            new_board.make_move(move);
            visited.push_back(new_board);
            queue.push(new_board);
        }
    }
    std::cout << "Visited " << visited.size() << " boards" << std::endl;
}
