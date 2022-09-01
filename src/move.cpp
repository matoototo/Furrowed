#include "move.hpp"
#include "constants.hpp"

std::string Move::to_str() const {
    std::string str;
    if (castling) {
        if (castling == CASTLE_KW || castling == CASTLE_KB) {
            str = "O-O";
        } else {
            str = "O-O-O";
        }
    } else {
        if (promotion) {
            str = index_to_coord(from) + index_to_coord(to) + (char)tolower(piece_str_map.at(promotion));
        } else {
            str = index_to_coord(from) + index_to_coord(to);
        }
    }
    return str;
}
