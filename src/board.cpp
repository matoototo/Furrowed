#include <stdexcept>
#include <iostream>
#include <unordered_set>

#include "board.hpp"
#include "constants.hpp"

void Board::reset_board() {
    is_white = true;
    castle_K = false;
    castle_Q = false;
    castle_k = false;
    castle_q = false;
    en_passant = -1;
    fifty_move = 0;
    move_number = 1;
    board = {
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7
    };
}

void Board::set_FEN(const std::string &FEN) {
    // white is uppercase, black is lowercase
    // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
    reset_board();

    std::unordered_set<char> integers = {'1', '2', '3', '4', '5', '6', '7', '8'};

    uint index = 21;

    for (auto c : FEN) {
        if (integers.find(c) != integers.end()) {
            index += (c - '0');
        } else if (piece_map.find(c) != piece_map.end()) {
            board[index] = piece_map.at(c);
            index++;
        } else if (c == '/') {
            index += 2;
        } else if (c == ' ') {
            break;
        } else {
            throw std::runtime_error("Invalid FEN, failed to parse board");
        }
    }

    std::string after_board = FEN.substr(FEN.find(' ')+1);
    if (after_board[0] == 'w') {
        is_white = true;
    } else if (after_board[0] == 'b') {
        is_white = false;
    } else {
        throw std::runtime_error("Invalid FEN, failed to parse colour");
    }

    std::string after_color = after_board.substr(2);
    std::string castling = after_color.substr(0, after_color.find(' '));

    if (castling.find('K') != std::string::npos) {
        castle_K = true;
    } else if (castling.find('Q') != std::string::npos) {
        castle_Q = true;
    } else if (castling.find('k') != std::string::npos) {
        castle_k = true;
    } else if (castling.find('q') != std::string::npos) {
        castle_q = true;
    }

    std::string after_castling = after_color.substr(after_color.find(' ')+1);
    std::string en_passant = after_castling.substr(0, after_castling.find(' '));
    if (en_passant == "-") {
        this->en_passant = -1;
    } else {
        this->en_passant = square_map.at(en_passant);
    }

    std::string after_en_passant = after_castling.substr(after_castling.find(' ')+1);
    fifty_move = std::stoi(after_en_passant.substr(0, after_en_passant.find(' ')));
    move_number = std::stoi(after_en_passant.substr(after_en_passant.find(' ')+1));
}
