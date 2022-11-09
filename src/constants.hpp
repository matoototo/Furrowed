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

const std::unordered_map<int, std::string> index_map = {
    {28, "a8"}, {27, "b8"}, {26, "c8"}, {25, "d8"}, {24, "e8"}, {23, "f8"}, {22, "g8"}, {21, "h8"},
    {38, "a7"}, {37, "b7"}, {36, "c7"}, {35, "d7"}, {34, "e7"}, {33, "f7"}, {32, "g7"}, {31, "h7"},
    {48, "a6"}, {47, "b6"}, {46, "c6"}, {45, "d6"}, {44, "e6"}, {43, "f6"}, {42, "g6"}, {41, "h6"},
    {58, "a5"}, {57, "b5"}, {56, "c5"}, {55, "d5"}, {54, "e5"}, {53, "f5"}, {52, "g5"}, {51, "h5"},
    {68, "a4"}, {67, "b4"}, {66, "c4"}, {65, "d4"}, {64, "e4"}, {63, "f4"}, {62, "g4"}, {61, "h4"},
    {78, "a3"}, {77, "b3"}, {76, "c3"}, {75, "d3"}, {74, "e3"}, {73, "f3"}, {72, "g3"}, {71, "h3"},
    {88, "a2"}, {87, "b2"}, {86, "c2"}, {85, "d2"}, {84, "e2"}, {83, "f2"}, {82, "g2"}, {81, "h2"},
    {98, "a1"}, {97, "b1"}, {96, "c1"}, {95, "d1"}, {94, "e1"}, {93, "f1"}, {92, "g1"}, {91, "h1"}
};

const std::unordered_map<int, int> index_to_canon = {
    {28, 63}, {27, 62}, {26, 61}, {25, 60}, {24, 59}, {23, 58}, {22, 57}, {21, 56},
    {38, 55}, {37, 54}, {36, 53}, {35, 52}, {34, 51}, {33, 50}, {32, 49}, {31, 48},
    {48, 47}, {47, 46}, {46, 45}, {45, 44}, {44, 43}, {43, 42}, {42, 41}, {41, 40},
    {58, 39}, {57, 38}, {56, 37}, {55, 36}, {54, 35}, {53, 34}, {52, 33}, {51, 32},
    {68, 31}, {67, 30}, {66, 29}, {65, 28}, {64, 27}, {63, 26}, {62, 25}, {61, 24},
    {78, 23}, {77, 22}, {76, 21}, {75, 20}, {74, 19}, {73, 18}, {72, 17}, {71, 16},
    {88, 15}, {87, 14}, {86, 13}, {85, 12}, {84, 11}, {83, 10}, {82, 9}, {81, 8},
    {98, 7}, {97, 6}, {96, 5}, {95, 4}, {94, 3}, {93, 2}, {92, 1}, {91, 0}
};


const std::vector<int> white_promotions = {KNIGHT_W, BISHOP_W, ROOK_W, QUEEN_W};
const std::vector<int> black_promotions = {KNIGHT_B, BISHOP_B, ROOK_B, QUEEN_B};

#define A8 28
#define B8 27
#define C8 26
#define D8 25
#define E8 24
#define F8 23
#define G8 22
#define H8 21
#define A7 38
#define B7 37
#define C7 36
#define D7 35
#define E7 34
#define F7 33
#define G7 32
#define H7 31
#define A6 48
#define B6 47
#define C6 46
#define D6 45
#define E6 44
#define F6 43
#define G6 42
#define H6 41
#define A5 58
#define B5 57
#define C5 56
#define D5 55
#define E5 54
#define F5 53
#define G5 52
#define H5 51
#define A4 68
#define B4 67
#define C4 66
#define D4 65
#define E4 64
#define F4 63
#define G4 62
#define H4 61
#define A3 78
#define B3 77
#define C3 76
#define D3 75
#define E3 74
#define F3 73
#define G3 72
#define H3 71
#define A2 88
#define B2 87
#define C2 86
#define D2 85
#define E2 84
#define F2 83
#define G2 82
#define H2 81
#define A1 98
#define B1 97
#define C1 96
#define D1 95
#define E1 94
#define F1 93
#define G1 92
#define H1 91
