#pragma once

#include "move.hpp"
#include "board.hpp"

#include <utility>

void BFS(const Board&, int);
void DFS(const Board&, int);
std::pair<int, Move> negamax(const Board&, int);
