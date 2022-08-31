#include <iostream>
#include <stdexcept>
#include <functional>
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
    ply_number = 1;
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
            board[int(index/10) * 10 + 9 - index % 10] = piece_map.at(c);
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
    }
    if (castling.find('Q') != std::string::npos) {
        castle_Q = true;
    }
    if (castling.find('k') != std::string::npos) {
        castle_k = true;
    }
    if (castling.find('q') != std::string::npos) {
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
    ply_number = 2*std::stoi(after_en_passant.substr(after_en_passant.find(' ')+1));
}

void Board::add_moves(std::vector<Move>& moves, const std::vector<int>& directions, const int start, bool slide, int target = 0) {
    for (auto dir : directions) {
        int index = start + dir;
        do {
            if (board[index] == OUT) break;
            if (target != 0 && board[index] != target && board[index] != BLANK) break;
            if (board[index] != BLANK) {
                if (is_white && board[index] < 0)
                    moves.push_back(Move(start, index));
                else if (!is_white && board[index] > 0)
                    moves.push_back(Move(start, index));
                break;
            } else {
                if (target == 0) moves.push_back(Move(start, index));
            }
            index += dir;
        } while (true && slide);
    }
}

void Board::add_attackers(std::vector<int>& attackers, const int square) {
    // this is done by placing a pseudo-piece on that figure of each type, and checking
    // if any of the squares it attacks are occupied by the same piece of an opposite colour
    int sign = is_white ? -1 : 1;
    std::vector<Move> moves;
    std::vector<int> pawn_directions = {sign*9, sign*11};
    add_moves(moves, pawn_directions, square, false, PAWN_W*sign);
    std::vector<int> knight_directions = {-21, -19, -12, -8, 8, 12, 19, 21};
    add_moves(moves, knight_directions, square, false, KNIGHT_W*sign);
    std::vector<int> bishop_directions = {-9, -11, 11, 9};
    add_moves(moves, bishop_directions, square, true, BISHOP_W*sign);
    std::vector<int> rook_directions = {-1, -10, 1, 10};
    add_moves(moves, rook_directions, square, true, ROOK_W*sign);
    std::vector<int> queen_directions = {-1, -10, 1, 10, -11, -9, 9, 11};
    add_moves(moves, queen_directions, square, true, QUEEN_W*sign);
    std::vector<int> king_directions = {-1, -10, 1, 10, -11, -9, 9, 11};
    add_moves(moves, king_directions, square, false, KING_W*sign);

    for (auto move : moves) {
        attackers.push_back(move.to);
    }
}

#define generator_sig std::vector<Move>& moves, const int start

inline void Board::add_promotions(generator_sig, const int to) {
    std::vector<int> target_promotions = is_white ? white_promotions : black_promotions;
    for (auto promotion : target_promotions) {
        moves.push_back(Move(start, to, promotion));
    }
}

inline void Board::add_pawn_moves(generator_sig) {
    int sign = is_white ? -1 : 1;
    int promotion_rank = is_white ? 2 : 9;
    int second_rank = is_white ? 8 : 3;
    int current_rank = start / 10;
    int to_rank = current_rank + sign*1;

    if (board[start + 10*sign] == BLANK) {
        if (to_rank == promotion_rank)
            add_promotions(moves, start, start + 10*sign);
        else
            moves.push_back(Move(start, start + 10*sign));
        if (current_rank == second_rank && board[start + 20*sign] == 0)
            moves.push_back(Move(start, start + 20*sign));
    }


    int to = start + 11*sign;
    if ((board[to]*board[start] < 0 && board[to] != OUT) || to == en_passant) {
        if (to_rank == promotion_rank)
            add_promotions(moves, start, to);
        else
            moves.push_back(Move(start, to));
    }

    to = start + 9*sign;
    if ((board[to]*board[start] < 0 && board[to] != OUT) || to == en_passant) {
        if (to_rank == promotion_rank)
            add_promotions(moves, start, to);
        else
            moves.push_back(Move(start, to));
    }
}

inline void Board::add_knight_moves(generator_sig) {
    std::vector<int> directions = {-21, -19, -12, -8, 8, 12, 19, 21};
    add_moves(moves, directions, start, false);
}

inline void Board::add_bishop_moves(generator_sig) {
    std::vector<int> directions = {-9, -11, 11, 9};
    add_moves(moves, directions, start, true);
}

inline void Board::add_rook_moves(generator_sig) {
    std::vector<int> directions = {-1, -10, 1, 10};
    add_moves(moves, directions, start, true);
}

inline void Board::add_queen_moves(generator_sig) {
    std::vector<int> directions = {-1, -10, 1, 10, -11, -9, 9, 11};
    add_moves(moves, directions, start, true);
}

inline void Board::add_king_moves(generator_sig) {
    std::vector<int> directions = {-1, -10, 1, 10, -11, -9, 9, 11};
    add_moves(moves, directions, start, false);


    std::vector<int> attackers = {};
    add_attackers(attackers, start);
    if (attackers.size() != 0) return;

    int b_square, c_square, d_square, f_square, g_square, kingside, queenside;
    if (is_white) {
        b_square = B8; c_square = C8; d_square = D8;
        f_square = F8; g_square = G8;
        kingside = castle_K * CASTLE_KW; queenside = castle_Q * CASTLE_QW;
    } else {
        b_square = B1; c_square = C1; d_square = D1;
        f_square = F1; g_square = G1;
        kingside = castle_k * CASTLE_KB; queenside = castle_q * CASTLE_QB;
    }

    if (kingside) {
        if (board[f_square] == BLANK && board[g_square] == BLANK) {
            add_attackers(attackers, f_square);
            add_attackers(attackers, g_square);
            if (attackers.size() == 0) {
                moves.push_back(Move(start, g_square, 0, kingside));
            }
        }

    }
    attackers = {};
    if (queenside) {
        if (board[b_square] == BLANK && board[c_square] == BLANK && board[d_square] == BLANK) {
            add_attackers(attackers, c_square);
            add_attackers(attackers, d_square);
            if (attackers.size() == 0)
                moves.push_back(Move(start, c_square, 0, queenside));
        }
    }
}

std::vector<Move> Board::pseudo_legal_moves() {
    std::vector<Move> pseudo_legal_moves;
    std::unordered_map<int, std::function<void(generator_sig)>> generators = {
        {PAWN_W, [this](generator_sig){add_pawn_moves(moves, start);}},
        {PAWN_B, [this](generator_sig){add_pawn_moves(moves, start);}},
        {KNIGHT_W, [this](generator_sig){add_knight_moves(moves, start);}},
        {KNIGHT_B, [this](generator_sig){add_knight_moves(moves, start);}},
        {BISHOP_W, [this](generator_sig){add_bishop_moves(moves, start);}},
        {BISHOP_B, [this](generator_sig){add_bishop_moves(moves, start);}},
        {ROOK_W, [this](generator_sig){add_rook_moves(moves, start);}},
        {ROOK_B, [this](generator_sig){add_rook_moves(moves, start);}},
        {QUEEN_W, [this](generator_sig){add_queen_moves(moves, start);}},
        {QUEEN_B, [this](generator_sig){add_queen_moves(moves, start);}},
        {KING_W, [this](generator_sig){add_king_moves(moves, start);}},
        {KING_B, [this](generator_sig){add_king_moves(moves, start);}}
    };

    for (int i = 21; i < 99; ++i) {
        if (i % 10 == 9) {
            i += 1;
            continue;
        }
        else if (board[i] == BLANK || (board[i] > 0 && !is_white) || (board[i] < 0 && is_white)) {
            continue;
        }
        int piece = board[i];
        generators.at(piece)(pseudo_legal_moves, i);
    }
    return pseudo_legal_moves;
}

std::vector<Move> Board::legal_moves() {
    int king_square = find_king();
    if (king_square == -1) {
        throw std::runtime_error("No king found");
    }
    std::vector<Move> legal_moves;
    for (auto move : pseudo_legal_moves()) {
        if (move_is_legal(move, king_square)) {
            legal_moves.push_back(move);
        }
    }
    return legal_moves;
}

int Board::find_king() {
    int sign = is_white ? 1 : -1;
    for (int i = 21; i < 99; ++i) {
        if (i % 10 == 9) {
            i += 1;
            continue;
        }
        else if (board[i] == KING_W*sign) {
            return i;
        }
    }
    return -1;
}

bool Board::is_in_check(int king_square) {
    std::vector<int> attackers = {};
    add_attackers(attackers, king_square);
    return attackers.size() != 0;
}

bool Board::move_is_legal(const Move& move, int king_square) {
    Board copy_board = *this;
    copy_board.make_move(move);
    copy_board.is_white = !copy_board.is_white;
    if (move.from == king_square) {
        king_square = move.to;
    }
    return !copy_board.is_in_check(king_square);
}

void Board::print_board() const {
    for (int i = 21; i < 99; ++i) {
        int real_i = int(i / 10) * 10 + 9 - (i % 10); // flip horizontally
        if (i % 10 == 9) {
            i += 1;
            std::cout << '\n';
            continue;
        }
        if (board[real_i] == BLANK)
            std::cout << ' ';
        else {
            std::cout << piece_str_map.at(board[real_i]);
        }
    }
    std::cout << std::endl;
}

void Board::make_move(const Move& move) {
    int sign = (board[move.from] > 0) ? -1 : 1;

    if (board[move.to] != 0 || sign*board[move.from] == PAWN_B) {
        fifty_move = 0;
    } else {
        fifty_move += 1;
    }

    if (move.to == en_passant) {
        board[move.to - sign * 10] = 0;
    }

    en_passant = 0;

    if (board[move.from] == PAWN_W && (move.from/10 - move.to/10) == 2) {
        en_passant = move.from - 10;
    } else if (board[move.from] == PAWN_B && (move.to/10 - move.from/10) == 2) {
        en_passant = move.from + 10;
    }

    board[move.to] = board[move.from];
    board[move.from] = 0;

    if (move.promotion != 0) {
        board[move.to] = move.promotion;
    }

    if (move.castling == CASTLE_KW) {
        board[F1] = board[H1];
        board[H1] = 0;
    } else if (move.castling == CASTLE_QW) {
        board[D1] = board[A1];
        board[A1] = 0;
    } else if (move.castling == CASTLE_KB) {
        board[F8] = board[H8];
        board[H8] = 0;
    } else if (move.castling == CASTLE_QB) {
        board[D8] = board[A8];
        board[A8] = 0;
    }

    // remove castling rights on king/rook move
    if (board[move.to] == KING_W) {
        castle_K = false;
        castle_Q = false;
    } else if (board[move.to] == KING_B) {
        castle_k = false;
        castle_q = false;
    } else if (board[move.to] == ROOK_W) {
        if (move.from == H1) {
            castle_K = false;
        } else if (move.from == A1) {
            castle_Q = false;
        }
    } else if (board[move.to] == ROOK_B) {
        if (move.from == H8) {
            castle_k = false;
        } else if (move.from == A8) {
            castle_q = false;
        }
    }

    // if something moves to rook positions, we know we can't castle anymore
    if (move.to == H1) {
        castle_K = false;
    } else if (move.to == A1) {
        castle_Q = false;
    } else if (move.to == H8) {
        castle_k = false;
    } else if (move.to == A8) {
        castle_q = false;
    }

    ply_number += 1;
    is_white = !is_white;
}
