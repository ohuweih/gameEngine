#include "../header/GameState.h"
#include "../header/Knight.h"

// knight move
bool Knight::is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) {
    int row_diff = std::abs(start_row - end_row);
    int col_diff = std::abs(start_col - end_col);

    // The L shape
    if ((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)) {
        return true;
    }

    return false;
}
