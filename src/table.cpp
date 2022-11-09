#include "table.hpp"
#include "board.hpp"
#include "constants.hpp"

#include <random>
#include <climits>
#include <iostream>
#include <stdexcept>

void Table::init_zobrist() {
    std::default_random_engine generator;
    std::uniform_int_distribution<long long> distribution(0, LONG_LONG_MAX);
    for (auto i = 0; i < 64; ++i) {
        for (auto j = 0; j < 12; ++j) {
            zobrist[i][j] = distribution(generator);
        }
    }
    btm_hash = distribution(generator); // black to move
    wk_hash = distribution(generator); // w kingside castle
    wq_hash = distribution(generator);
    bk_hash = distribution(generator);
    bq_hash = distribution(generator);
    // en passant?
}

void Table::hash_piece(unsigned long long& hash, int index_10x12, int piece) const {
    int index = std::abs(piece) - 1;
    if (piece < 0) {
        index += 6;
    }
    hash ^= zobrist[index_to_canon.at(index_10x12)][index];
}

unsigned long long Table::zobrist_hash(const Board& b) const {
    unsigned long long hash = 0;
    if (!b.is_white) hash ^= btm_hash;
    if (b.castle_K) hash ^= wk_hash;
    if (b.castle_Q) hash ^= wq_hash;
    if (b.castle_k) hash ^= bk_hash;
    if (b.castle_q) hash ^= bq_hash;

    for (int i = H8; i <= A1; ++i) {
        if (i % 10 == 9) {
            i += 1;
            continue;
        }
        if (i % 10 == 0) {
            continue;
        }
        if (b.board[i] == 0) {
            continue;
        } else {
            hash_piece(hash, i, b.board[i]);
        }
    }
    return hash;
}

bool Table::add(const Board& b, Move best, int value, int depth, int type) {
    // unsigned long long hash = zobrist_hash(b);
    unsigned long long hash = b.hash;
    // std::cout << hash << std::endl;
    Entry e = {
        best,
        b.to_fen(),
        value,
        depth,
        type
    };
    data[hash] = e;
    this->queue.push(hash);
    if (data.size() > size) {
        auto front = queue.front();
        data.erase(front);
        queue.pop();
    }
    return true;
}


std::pair<Entry, bool> Table::probe(const Board& b) {
    // auto hash = zobrist_hash(b);
    unsigned long long hash = b.hash;
    auto entry = Entry();
    bool hit = true;
    try {
        entry = data.at(hash);
    } catch (std::out_of_range e) {
        hit = false; // miss
    }
    return {entry, hit};
}

