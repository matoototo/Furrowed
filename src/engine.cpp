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
    long long thinktime = board.is_white ? t.wtime / 40 : t.btime / 40;
    if (t.infinite) {
        thinktime = 1e9;
    }
    // current time
    auto start = now();

    std::cout << "info string thinking for " << thinktime << "ms" << std::endl;

    long long think_until = now() + thinktime;

    for (int depth = 1; think_until > now() && !stop; ++depth) {
        // search
        std::pair<int, Move> p = negamax(board, depth, stop, think_until);
        if (!stop) { // we shouldn't trust the output if it aborted
            set_move(p.second);
            // logging here, maybe move it outside of Engine with a callback?
            std::cout << "info depth " << depth << std::endl;
            std::cout << "info score cp " << p.first
                      <<  " time " << now() - start
                      << " pv " << p.second.to_str()
                      << std::endl;
        }
    }
    stop = true;
    if (move != Move()) std::cout << "bestmove " << move.to_str() << std::endl;
}
