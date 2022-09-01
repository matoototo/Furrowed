#pragma once

#include "move.hpp"
#include "board.hpp"

#include <atomic>
#include <utility>
#include <functional>

void BFS(const Board&, int);
void DFS(const Board&, int);
std::pair<int, Move> negamax(const Board&, int, std::atomic<bool>&, long long);
