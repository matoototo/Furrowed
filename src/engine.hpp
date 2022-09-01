#pragma once

#include "board.hpp"
#include "time.hpp"

#include <mutex>
#include <thread>
#include <atomic>

struct Engine {
    Engine() : move_mutex(), stop(true) {}
    Engine(Board board): board(board), move_mutex(), stop(true) {}

    void think(const Time& t);
    void set_move(Move move);

    Board board;
    Move move;
    std::mutex move_mutex;
    std::thread thread;
    std::atomic<bool> stop;
};
