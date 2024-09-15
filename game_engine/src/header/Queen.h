#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"
#include "GameState.h"

class Queen : public ChessPiece {
public:
    Queen(const std::string& color) : ChessPiece("Queen", color) {}
    bool is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) override;
};

#endif // QUEEN_H

