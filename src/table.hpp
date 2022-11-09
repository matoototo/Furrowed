#pragma once

#include "move.hpp"

#include <queue>
#include <iterator>
#include <unordered_map>


struct Entry {
    Move best;
    std::string FEN;
    int value;
    int depth;
    int type;
};

struct Board;

struct Table {
    Table(int megabytes) {
        // Move 16B, value, depth, type 4B = 28B/entry
        size = 1024*1024*megabytes / (28*11);
        init_zobrist();
    }
    int size;
    unsigned long long zobrist[64][12];
    unsigned long long btm_hash;
    unsigned long long wk_hash;
    unsigned long long wq_hash;
    unsigned long long bk_hash;
    unsigned long long bq_hash;
    std::unordered_map<unsigned long long, Entry> data;
    std::queue<unsigned long long> queue;
    void init_zobrist();
    void hash_piece(unsigned long long&, int, int) const;
    unsigned long long zobrist_hash(const Board&) const;
    bool add(const Board&, Move, int, int, int);
    std::pair<Entry, bool> probe(const Board&);
};
