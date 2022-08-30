#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <unordered_set>

#include "move.hpp"

struct Board {
    Board() {
        reset_board();
    }
    Board(const std::string& FEN) {
        set_FEN(FEN);
    }

    void reset_board();
    void set_FEN(const std::string&);
    void print_board() const;
    void make_move(const Move&);
    std::vector<Move> legal_moves();
    std::vector<Move> pseudo_legal_moves();

    std::vector<int> board;
    bool is_white;
    bool castle_K;
    bool castle_Q;
    bool castle_k;
    bool castle_q;
    int en_passant;
    uint fifty_move;
    int ply_number;

    bool operator==(const Board& other) const {
        return (
            board == other.board &&
            is_white == other.is_white &&
            castle_K == other.castle_K &&
            castle_Q == other.castle_Q &&
            castle_k == other.castle_k &&
            castle_q == other.castle_q &&
            en_passant == other.en_passant &&
            fifty_move == other.fifty_move &&
            ply_number == other.ply_number
        );
    };

    private:

    void add_moves(std::vector<Move>&, const std::vector<int>&, const int, bool, int);
    void add_attackers(std::vector<int>&, const int);
    void add_promotions(std::vector<Move>&, const int, const int);
    void add_pawn_moves(std::vector<Move>&, const int);
    void add_knight_moves(std::vector<Move>&, const int);
    void add_bishop_moves(std::vector<Move>&, const int);
    void add_rook_moves(std::vector<Move>&, const int);
    void add_queen_moves(std::vector<Move>&, const int);
    void add_king_moves(std::vector<Move>&, const int);
    bool move_is_legal(const Move&, int);
    bool is_in_check(const int);
    int find_king();
};
