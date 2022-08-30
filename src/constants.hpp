#pragma once

#define BLANK 0
#define OUT 7

#define PAWN_W 1
#define KNIGHT_W 2
#define BISHOP_W 3
#define ROOK_W 4
#define QUEEN_W 5
#define KING_W 6

#define PAWN_B -1
#define KNIGHT_B -2
#define BISHOP_B -3
#define ROOK_B -4
#define QUEEN_B -5
#define KING_B -6

#define CASTLE_KW 1
#define CASTLE_QW 2
#define CASTLE_KB 3
#define CASTLE_QB 4

#include <string>
#include <vector>
#include <unordered_map>

const std::unordered_map<char, int> piece_map = {
    {'P', PAWN_W}, {'N', KNIGHT_W}, {'B', BISHOP_W}, {'R', ROOK_W}, {'Q', QUEEN_W}, {'K', KING_W},
    {'p', PAWN_B}, {'n', KNIGHT_B}, {'b', BISHOP_B}, {'r', ROOK_B}, {'q', QUEEN_B}, {'k', KING_B}
};

const std::unordered_map<int, char> piece_str_map = {
    {PAWN_W, 'P'}, {KNIGHT_W, 'N'}, {BISHOP_W, 'B'}, {ROOK_W, 'R'}, {QUEEN_W, 'Q'}, {KING_W, 'K'},
    {PAWN_B, 'p'}, {KNIGHT_B, 'n'}, {BISHOP_B, 'b'}, {ROOK_B, 'r'}, {QUEEN_B, 'q'}, {KING_B, 'k'}
};

const std::unordered_map<std::string, int> square_map = {
    {"a8", 28}, {"b8", 27}, {"c8", 26}, {"d8", 25}, {"e8", 24}, {"f8", 23}, {"g8", 22}, {"h8", 21},
    {"a7", 38}, {"b7", 37}, {"c7", 36}, {"d7", 35}, {"e7", 34}, {"f7", 33}, {"g7", 32}, {"h7", 31},
    {"a6", 48}, {"b6", 47}, {"c6", 46}, {"d6", 45}, {"e6", 44}, {"f6", 43}, {"g6", 42}, {"h6", 41},
    {"a5", 58}, {"b5", 57}, {"c5", 56}, {"d5", 55}, {"e5", 54}, {"f5", 53}, {"g5", 52}, {"h5", 51},
    {"a4", 68}, {"b4", 67}, {"c4", 66}, {"d4", 65}, {"e4", 64}, {"f4", 63}, {"g4", 62}, {"h4", 61},
    {"a3", 78}, {"b3", 77}, {"c3", 76}, {"d3", 75}, {"e3", 74}, {"f3", 73}, {"g3", 72}, {"h3", 71},
    {"a2", 88}, {"b2", 87}, {"c2", 86}, {"d2", 85}, {"e2", 84}, {"f2", 83}, {"g2", 82}, {"h2", 81},
    {"a1", 98}, {"b1", 97}, {"c1", 96}, {"d1", 95}, {"e1", 94}, {"f1", 93}, {"g1", 92}, {"h1", 91}
};

const std::vector<int> white_promotions = {KNIGHT_W, BISHOP_W, ROOK_W, QUEEN_W};
const std::vector<int> black_promotions = {KNIGHT_B, BISHOP_B, ROOK_B, QUEEN_B};
