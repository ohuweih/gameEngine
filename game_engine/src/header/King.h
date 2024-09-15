// King.h
#ifndef KING_H
#define KING_H

#include "ChessPiece.h"

class King : public ChessPiece {
public:
    // Constructor that initializes the king with a color
    King(const std::string& color) : ChessPiece("King", color) {}

    // The King moves one square in any direction
    bool is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) override;
};

#endif
