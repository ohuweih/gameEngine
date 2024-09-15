#include "../header/Queen.h"
#include "../header/Rook.h"
#include "../header/Bishop.h"

bool Queen::is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) {
    // Queen moves like a combination of Rook and Bishop
    Rook rook(color);
    Bishop bishop(color);
    
    // A queen can move like either a rook or a bishop
    return rook.is_valid_move(game_state, start_row, start_col, end_row, end_col) ||
           bishop.is_valid_move(game_state, start_row, start_col, end_row, end_col);
}

