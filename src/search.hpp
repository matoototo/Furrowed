#pragma once

#include "move.hpp"
#include "board.hpp"
#include "engine.hpp"

#include <atomic>
#include <utility>
#include <functional>

void BFS(const Board&, int);
void DFS(const Board&, int);
std::pair<int, Move> negamax(const Board&, int, std::atomic<bool>&, long long);
std::pair<int, Move> alpha_beta(Engine&, const Board&, int, int, int, std::atomic<bool>&, long long);
