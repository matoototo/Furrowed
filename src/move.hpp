#pragma once

struct Board;

#include <string>

struct Move {
    Move() : from(0), to(0), promotion(0), castling(0) {}
    Move(int from, int to, int promotion = 0, int castling = 0) : from(from), to(to), promotion(promotion), castling(castling) {}

    bool operator!=(const Move& other) const {
        return from != other.from || to != other.to || promotion != other.promotion || castling != other.castling;
    }

    std::string index_to_coord(int index) const {
        return std::string(1, 'h' + 1 - (index % 10)) + std::string(1, '8' - (index - 20) / 10);
    }
    std::string to_str() const;
    static Move from_str(std::string, Board&);

    int from;
    int to;
    int promotion;
    int castling;
};
