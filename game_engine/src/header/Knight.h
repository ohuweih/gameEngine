#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"
#include "GameState.h"

class Knight : public ChessPiece {
public:
    Knight(const std::string& color) : ChessPiece("Knight", color) {}
    bool is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) override;
};

#endif // KNIGHT_H
