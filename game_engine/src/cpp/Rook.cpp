#include "../header/GameState.h"
#include "../header/Rook.h"
#include <iostream>


// Rook move
bool Rook::is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) {
    if (start_row != end_row && start_col != end_col) {
            return false;
    }

    //check if path is clear
    if (start_row == end_row) {
        int step = (start_col < end_col) ? 1 : -1;
        for (int col = start_col + step; col != end_col; col += step) {
            if (game_state.board[start_row][col]->name != "") return false; //Blocked
        }
    } else {
        int step = (start_row < end_row) ? 1 : -1;
        for (int row = start_row + step; row != end_row; row += step) {
            if (game_state.board[row][start_col]->name != "") return false; //Blocked again
        }
    }

    return true;
}
