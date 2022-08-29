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

#define square int

#include <string>
#include <vector>
#include <unordered_map>

const std::unordered_map<char, int> piece_map = {
    {'P', PAWN_W}, {'N', KNIGHT_W}, {'B', BISHOP_W}, {'R', ROOK_W}, {'Q', QUEEN_W}, {'K', KING_W},
    {'p', PAWN_B}, {'n', KNIGHT_B}, {'b', BISHOP_B}, {'r', ROOK_B}, {'q', QUEEN_B}, {'k', KING_B}
};

const std::unordered_map<std::string, int> square_map = {
    {"a1", 21}, {"b1", 22}, {"c1", 23}, {"d1", 24}, {"e1", 25}, {"f1", 26}, {"g1", 27}, {"h1", 28},
    {"a2", 31}, {"b2", 32}, {"c2", 33}, {"d2", 34}, {"e2", 35}, {"f2", 36}, {"g2", 37}, {"h2", 38},
    {"a3", 41}, {"b3", 42}, {"c3", 43}, {"d3", 44}, {"e3", 45}, {"f3", 46}, {"g3", 47}, {"h3", 48},
    {"a4", 51}, {"b4", 52}, {"c4", 53}, {"d4", 54}, {"e4", 55}, {"f4", 56}, {"g4", 57}, {"h4", 58},
    {"a5", 61}, {"b5", 62}, {"c5", 63}, {"d5", 64}, {"e5", 65}, {"f5", 66}, {"g5", 67}, {"h5", 68},
    {"a6", 71}, {"b6", 72}, {"c6", 73}, {"d6", 74}, {"e6", 75}, {"f6", 76}, {"g6", 77}, {"h6", 78},
    {"a7", 81}, {"b7", 82}, {"c7", 83}, {"d7", 84}, {"e7", 85}, {"f7", 86}, {"g7", 87}, {"h7", 88},
    {"a8", 91}, {"b8", 92}, {"c8", 93}, {"d8", 94}, {"e8", 95}, {"f8", 96}, {"g8", 97}, {"h8", 98}
};

const std::vector<int> white_promotions = {KNIGHT_W, BISHOP_W, ROOK_W, QUEEN_W};
const std::vector<int> black_promotions = {KNIGHT_B, BISHOP_B, ROOK_B, QUEEN_B};
