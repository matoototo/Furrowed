#pragma once

#include "move.hpp"
#include "board.hpp"
#include "engine.hpp"

#include <atomic>
#include <utility>
#include <functional>

std::pair<int, Move> alpha_beta(Engine&, const Board&, int, int, int, std::atomic<bool>&, long long);
