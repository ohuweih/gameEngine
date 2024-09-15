#include "../header/GameState.h"
#include "../header/Bishop.h"
#include <iostream>

// bishop move
bool Bishop::is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) {
    if (std::abs(start_row - end_row) != std::abs(start_col - end_col)) {
            return false; // This is the diagonal move
    }

    // Check if path is clear
    int row_step = (start_row < end_row) ? 1 : -1;
    int col_step = (start_col < end_col) ? 1 : -1;
    int row = start_row + row_step;
    int col = start_col + col_step;
    while (row != end_row && col != end_col) {
        if (game_state.board[row][col]->name != "") return false; // Blocked
        row += row_step;
        col += col_step;
    }

    return true;
}
