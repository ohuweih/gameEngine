// Bishop.h
#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : public ChessPiece {
public:
    Bishop(const std::string& color) : ChessPiece("Bishop", color) {}

    bool is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) override; };

#endif
