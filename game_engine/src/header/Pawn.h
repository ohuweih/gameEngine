// Pawn.h
#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece {
public:
    Pawn(const std::string& color) : ChessPiece("Pawn", color) {}

    bool is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) override;}; 
#endif
