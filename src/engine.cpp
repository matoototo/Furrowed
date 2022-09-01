#include "time.hpp"
#include "engine.hpp"
#include "search.hpp"

#include <chrono>
#include <thread>
#include <iostream>

void Engine::set_move(Move move) {
    std::lock_guard<std::mutex> lock(move_mutex);
    this->move = move;
}

void Engine::think(const Time& t) {
    // currently only supports infinite and wtime/btime
    int thinktime = board.is_white ? t.wtime / 40 : t.btime / 40;
    if (t.infinite) {
        thinktime = 1e9;
    }
    // current time
    auto start = std::chrono::high_resolution_clock::now();

    for (int depth = 1; start + std::chrono::milliseconds(thinktime) > std::chrono::high_resolution_clock::now() && !stop; ++depth) {
        // search
        std::pair<int, Move> p = negamax(board, depth, stop);
        if (!stop) { // we shouldn't trust the output if it aborted
            set_move(p.second);
            // logging here, maybe move it outside of Engine with a callback?
            std::cout << "info depth " << depth << std::endl;
            std::cout << "info score cp " << p.first
                      <<  " time " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count()
                      << " pv " << p.second.to_str()
                      << std::endl;
        }
    }
    stop = true;
    if (move != Move()) std::cout << "bestmove " << move.to_str() << std::endl;
}
