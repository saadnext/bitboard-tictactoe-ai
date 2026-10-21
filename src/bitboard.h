#pragma once
#include <bitset>
#include <cassert>

constexpr int NUM_SQUARES = 9;
constexpr int NUM_SIDE = 2;

using Bitboard = std::bitset<NUM_SQUARES>;

constexpr bool is_valid_sq(int sq) { return sq >= 0 && sq < NUM_SQUARES; }

inline Bitboard square_bb(int sq) {
    assert(is_valid_sq(sq));
    return Bitboard{1} << sq;
}

inline bool test_bit(Bitboard bb, int sq) {
    assert(is_valid_sq(sq));
    return bb.test(sq);
}
