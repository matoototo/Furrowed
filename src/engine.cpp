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
    long long thinktime = board.is_white ? t.wtime / 20 : t.btime / 20;
    if (t.infinite) {
        thinktime = 1e9;
    }
    // current time
    auto start = now();
    board.generate_hash(table);
    nodes = 0;

    std::cout << "info string thinking for " << thinktime << "ms" << std::endl;

    // TODO: prefer allocating surplus to harder positions
    long long think_until = now() + thinktime + this->surplus;
    this->surplus = 0;

    std::vector<long long> depth_times;
    double factor = 4.0;
    double cutting_strength = 1.0;
    depth_times.reserve(32);

    for (int depth = 1; think_until > now() && !stop; ++depth) {
        // search
        long long depth_start = now();
        std::pair<int, Move> p = alpha_beta(*this, board, depth, -1e9, 1e9, stop, think_until);
        depth_times.push_back(now() - depth_start);

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

            // break early if definitely not enough time for next depth
            if (!t.infinite) {
                if (auto before_back = *(depth_times.end() - 2); depth_times.size() > 2) {
                    double current_factor = (double)(depth_times.back()+1)/(before_back+1);
                    factor = 0.8*factor + 0.2*current_factor;
                }
                std::cout << "info string budget: " << think_until - now() << '\n'
                          << "info string estimate: " << depth_times.back() * factor << '\n'
                          << "info string factor: " << factor << '\n'
                          << "info string cutting_strength: " << cutting_strength
                          << std::endl;
                if (depth_times.back() * factor * cutting_strength > think_until - now()) {
                    this->surplus += think_until - now(); // we've saved this much
                    std::cout << "info string halting search early" << std::endl;
                    break;
                }
            }
        }
    }
    stop = true;
    if (move != Move()) std::cout << "bestmove " << move.to_str() << std::endl;
}
