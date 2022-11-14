#pragma once

#include "board.hpp"
#include "time.hpp"
#include "table.hpp"

#include <mutex>
#include <thread>
#include <atomic>

struct Engine {
    Engine() : move_mutex(), stop(true), nodes(0) {}
    Engine(Board board): board(board), move_mutex(), stop(true) {}

    void think(const Time& t);
    void set_move(Move move);

    Board board;
    Move move;
    Table table{1024};
    std::mutex move_mutex;
    std::thread thread;
    std::atomic<bool> stop;
    std::atomic<int> nodes;
    std::atomic<long long> surplus{0};
};
