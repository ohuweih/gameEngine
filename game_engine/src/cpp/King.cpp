// King.cpp
#include "../header/GameState.h"
#include "../header/King.h"
#include <cmath>  // for std::abs

bool King::is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) {
    int row_diff = std::abs(start_row - end_row);
    int col_diff = std::abs(start_col - end_col);

    // Check if the king moves exactly one square in any direction
    if (row_diff <= 1 && col_diff <= 1) {
        // Make sure the target square is either empty or has an opponent's piece
        ChessPiece* target_piece = game_state.get_piece_at(end_row, end_col);
        if (target_piece->color != this->color) {
            return true;  // Valid move
        }
    }
    
    return false;  // Invalid move
}

