#ifndef PIECE_H  // Include guard to prevent multiple inclusion
#define PIECE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "MoveEntry.h"
#include "SpecialState.h"
#include "PieceTypes.h"

class SpecialState;
class GameState;


class Piece {
        public:
        Piece(Color color, int row, int col)
            : color(color), row(row), col(col) {}

        virtual ~Piece() = default;  // Default virtual destructor for polymorphism what ever that is

        virtual bool isValidMove(int newRow, int newCol, GameState& game_state) const = 0;

        void move(int newRow, int newCol) {
            // Update piece position
            row = newRow;
                col = newCol;
        }

        void logMove(int newRow, int newCol, int turnNumber) {
            movementLog.push_back(MoveEntry(row, col, newRow, newCol, turnNumber, getName()));
        }

        bool hasMoved() const { return !movementLog.empty();}

        const std::vector<MoveEntry>& getMovementLog() const { return movementLog; }

        int getRow() const { return row; }
        int getCol() const { return col; }
        Color getColor() const { return color; }
        virtual std::string getName() const = 0;
                virtual PieceType getType() const = 0;

        protected:
        int row;
        int col;
        Color color;
        std::vector<MoveEntry> movementLog;
};


class Pawn : public Piece {
    public:
        Pawn(Color color, int row, int col)
            : Piece(color, row, col) {}

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;
        PieceType getType() const override;
};

class Rook : public Piece {
    public:
        Rook(Color color, int row, int col)
         : Piece(color, row, col) {}

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;
        PieceType getType() const override;
};

class Knight : public Piece {
    public:
        Knight(Color color, int row, int col)
            : Piece(color, row, col) {}

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;
        PieceType getType() const override;

};

class Bishop : public Piece {
    public:
        Bishop(Color color, int row, int col)
            : Piece(color, row, col) {}

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;
        PieceType getType() const override;

};

class Queen : public Piece {
    public:
        Queen(Color color, int row, int col)
             : Piece(color, row, col) {}

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;
        PieceType getType() const override;

};

class King : public Piece {
    public:
        King(Color color, int row, int col)
             : Piece(color, row, col) {}

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;
        PieceType getType() const override;

};

#endif
