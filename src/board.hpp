#pragma once

#include <vector>
#include <string>
#include <cstdint>

struct Board {
    Board() {
        reset_board();
    }
    Board(const std::string& FEN) {
        set_FEN(FEN);
    }

    void reset_board();
    void set_FEN(const std::string&);

    std::vector<int> board;
    bool is_white;
    bool castle_K;
    bool castle_Q;
    bool castle_k;
    bool castle_q;
    int en_passant;
    uint fifty_move;
    uint move_number;
};
