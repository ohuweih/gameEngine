// Rook.h
#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"

class Rook : public ChessPiece {
public:
    Rook(const std::string& color) : ChessPiece("Rook", color) {}

    bool is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) override; };

#endif
