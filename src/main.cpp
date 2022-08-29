#include "board.hpp"

#include <chrono>
#include <iostream>

int main() {
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq e4 0 1");
    // time the execution of 1e6 calls to boards.pseudo_legal_moves()
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1e6; i++) {
        board.pseudo_legal_moves();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
    return 0;
}
