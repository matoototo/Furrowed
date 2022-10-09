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
        std::pair<int, Move> p = alpha_beta(*this, board, depth, -1e9, 1e9, stop, think_until);
        // we shouldn't trust the output if it aborted, but if it's d1 it's better than nothing
        if ((!stop && now() <= think_until) || depth == 1) {
            set_move(p.second);
            if (p.first == 1000000 || p.first == -1000000) break;
            // logging here, maybe move it outside of Engine with a callback?
            auto elapsed_ms = now() - start;
            std::cout << "info depth " << depth << std::endl;
            std::cout << "info score cp " << p.first
                      <<  " time " << elapsed_ms
                      << " nodes " << nodes
                      << " nps " << nodes*1000/(elapsed_ms+1)
                      << " pv " << p.second.to_str()
                      << std::endl;
        }
    }
    stop = true;
    if (move != Move()) std::cout << "bestmove " << move.to_str() << std::endl;
}
