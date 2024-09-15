#ifndef PIECEMOVEMENT_H
#define PIECEMOVEMENT_H
#include <string>
#include "GameState.h"

class PieceMovement {
    public:
    // Functions called from main cpp

        bool is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col);


    private:
        // Functions called with in the PieceMovement cpp
        bool is_square_attacked(GameState& game_state, int row, int col, const std::string& color);
        bool is_valid_pawn_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col, const std::string& color);
        bool is_valid_rook_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col);
        bool is_valid_knight_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col);
        bool is_valid_bishop_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col);
        bool is_valid_queen_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col);
        bool is_valid_king_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col);

};
#endif
