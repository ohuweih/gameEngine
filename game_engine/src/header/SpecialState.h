#ifndef SPECIALSTATE_H
#define SPECIALSTATE_H

#include "ChessPiece.h"
#include "GameState.h" 
#include "PieceTypes.h"

class GameState;
class Piece;

class SpecialState {
    public:
        // Function to check if castling is allowed
        static bool canCastle(GameState& game_state, const Piece* king, int newCol);

        // Function to check if the King is in check
        static bool isInCheck(const GameState& game_state, int row, int col, Color kingColor);

        // Function to check if the King moves through check (used in castling)
        static bool passesThroughCheck(GameState& game_state, const Piece* king, int newCol);
};

#endif // SPECIALSTATE_H
