#pragma once
#include "bitboard.h"
#include <cassert>
#include <iostream>

enum class Side : int { X, O };
enum class Winner : int { X, O, Draw, None };

constexpr int to_index(Side side) { return static_cast<int>(side); }
constexpr Side operator~(Side side) { return static_cast<Side>(to_index(side) ^ 1); }

class Board {
  private:
    Bitboard board_[NUM_SIDE]{};
    Bitboard all_occupancy_{};
    Side side_to_move_ = Side::X;
    static constexpr Bitboard winn_masks[8] = {
        0b000000111, 0b000111000, 0b111000000, 0b001001001,
        0b010010010, 0b100100100, 0b100010001, 0b001010100,
    };

  public:
    explicit Board() = default;
    void reset() { *this = Board{}; }
    Side current_side() const { return side_to_move_; }

    void set(int sq) {
        assert(is_valid_sq(sq));
        board_[to_index(side_to_move_)] |= square_bb(sq);
        all_occupancy_ |= square_bb(sq);
    }
    void clear(int sq) {
        assert(is_valid_sq(sq));
        board_[to_index(side_to_move_)] &= ~square_bb(sq);
        all_occupancy_ &= ~square_bb(sq);
    }
    bool is_valid_move(int sq) const {
        assert(is_valid_sq(sq));
        return !test_bit(all_occupancy_, sq);
    }
    bool is_winner(Side side) const {
        int idx = to_index(side);
        for (int i = 0; i < 8; ++i) {
            if ((board_[idx] & winn_masks[i]) == winn_masks[i]) {
                return true;
            }
        }
        return false;
    }
    Winner check_winner() const {
        if (is_winner(Side::X))
            return Winner::X;
        if (is_winner(Side::O))
            return Winner::O;
        if (all_occupancy_ == 0b111111111)
            return Winner::Draw;

        return Winner::None;
    }
    char side_to_move() const { return (side_to_move_ == Side::X) ? 'X' : 'O'; }
    void switch_side_to_move() { side_to_move_ = ~side_to_move_; }
    void print() const {
        for (int r = 0; r < 3; ++r) {
            std::cout << "\t";
            for (int c = 0; c < 3; ++c) {
                int sq = r * 3 + c;
                std::cout << "  ";
                if (test_bit(board_[to_index(Side::X)], sq)) {
                    std::cout << "X";
                } else if (test_bit(board_[to_index(Side::O)], sq)) {
                    std::cout << "O";
                } else {
                    std::cout << sq + 1;
                }
                std::cout << "  ";
                if (c < 2)
                    std::cout << "|";
            }
            if (r < 2)
                std::cout << "\n\t-----+-----+-----\n";
        }
        std::cout << "\n\n";
    }
};
