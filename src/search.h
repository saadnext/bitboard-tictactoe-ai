#pragma once
#include "bitboard.h"
#include "board.h"
#include <algorithm>
#include <limits>
#include <vector>

inline std::vector<int> get_valid_moves(const Board& board) {
    std::vector<int> valid_moves;
    valid_moves.reserve(NUM_SQUARES);
    for (int i = 0; i < NUM_SQUARES; ++i) {
        if (board.is_valid_move(i))
            valid_moves.push_back(i);
    }
    return valid_moves;
}

inline int minimax(Board& board, bool maximizing, int alpha, int beta) {
    Winner winner = board.check_winner();
    if (winner != Winner::None) {
        return (winner == Winner::X ? 1 : (winner == Winner::O ? -1 : 0));
    }
    std::vector<int> valid_moves = get_valid_moves(board);
    int value = maximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    for (const auto& mv : valid_moves) {
        board.set(mv);
        board.switch_side_to_move();
        int score = minimax(board, !maximizing, alpha, beta);
        value = maximizing ? std::max(value, score) : std::min(value, score);
        board.switch_side_to_move();
        board.clear(mv);

        if (maximizing) {
            alpha = std::max(alpha, value);
        } else {
            beta = std::min(beta, value);
        }
        if (beta <= alpha)
            break;
    }
    return value;
}

inline int find_best_move(Board& board) {
    bool maximizing = (board.side_to_move() == 'X');
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    std::vector<int> valid_moves = get_valid_moves(board);

    int best_move = valid_moves[0];
    int value = maximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    for (const auto& mv : valid_moves) {
        board.set(mv);
        board.switch_side_to_move();
        int score = minimax(board, !maximizing, alpha, beta);
        board.switch_side_to_move();
        board.clear(mv);
        if ((maximizing && score > value) || (!maximizing && score < value)) {
            value = score;
            best_move = mv;
        }
    }
    return best_move;
}
