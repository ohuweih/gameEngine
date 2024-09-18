#include "../header/GameState.h"

// Piece logic
bool Pawn::isValidMove(int newRow, int newCol, GameState& game_state) const {
    int rowDirection = (color == Color::White) ? -1 : 1;  // White pawns move up (-1), Black move down (+1)

    // Standard one-square forward move (no capture)
    if (newCol == col && newRow == row + rowDirection) {
        if (game_state.board[newRow][newCol] == nullptr) {
            return true;
        }
    }

    // Two-square forward move on the first move
    if (newCol == col && newRow == row + 2 * rowDirection) {
        if ((color == Color::White && row == 6) || (color == Color::Black && row == 1)) {
            if (game_state.board[row + rowDirection][newCol] == nullptr &&
                game_state.board[newRow][newCol] == nullptr) {
                return true;
            }
        }
    }

    // Diagonal capture
    if (abs(newCol - col) == 1 && newRow == row + rowDirection) {
        Piece* targetPiece = game_state.board[newRow][newCol];
        if (targetPiece != nullptr && targetPiece->getColor() != color) {
            return true;
            } 
        }
    return false;  // Capture opponent piece
}


std::string Pawn::getName() const {
    return (color == Color::White) ? "White Pawn" : "Black Pawn";
}


bool Rook::isValidMove(int newRow, int newCol, GameState& game_state) const {
    if (row != newRow && col != newCol) {
        return false;
    }

    // Check if the path is blocked
    if (row == newRow) {
        int step = (col < newCol) ? 1 : -1;
        for (int moveCol = col + step; moveCol !=newCol; moveCol += step) {
            if (game_state.board[newRow][moveCol]) return false;
        }
    } else if (col == newCol) {
         int step = (row < newRow) ? 1 : -1;
         for (int moveRow = row + step; moveRow !=newRow; moveRow += step) {
             if (game_state.board[moveRow][newCol]) return false;
         }
    }

    Piece* targetPiece = game_state.board[newRow][newCol];
    if (targetPiece) {
        if (targetPiece->getColor() != color) {
            return true;
        } else {
            return false;
        }
    }

    return true;
}

std::string Rook::getName() const {
    return (color == Color::White) ? "White Rook" : "Black Rook";
}


bool Knight::isValidMove(int newRow, int newCol, GameState& game_state) const {
    int rowDirection = (color == Color::White) ? -1 : 1;
    if (newCol == col && newRow == row + rowDirection) {
        if (game_state.board[newRow][newCol] == nullptr) {
             return true;
        }
    }
}

std::string Knight::getName() const {
    return (color == Color::White) ? "White Pawn" : "Black Pawn";
}


bool Bishop::isValidMove(int newRow, int newCol, GameState& game_state) const {
    int rowDirection = (color == Color::White) ? -1 : 1;
    if (newCol == col && newRow == row + rowDirection) {
        if (game_state.board[newRow][newCol] == nullptr) {
             return true;
        }
    }
}

std::string Bishop::getName() const {
    return (color == Color::White) ? "White Pawn" : "Black Pawn";
}


bool Queen::isValidMove(int newRow, int newCol, GameState& game_state) const {
    int rowDirection = (color == Color::White) ? -1 : 1;
    if (newCol == col && newRow == row + rowDirection) {
        if (game_state.board[newRow][newCol] == nullptr) {
             return true;
        }
    }
}

std::string Queen::getName() const {
    return (color == Color::White) ? "White Pawn" : "Black Pawn";
}


bool King::isValidMove(int newRow, int newCol, GameState& game_state) const {
    int rowDirection = (color == Color::White) ? -1 : 1;
    if (newCol == col && newRow == row + rowDirection) {
        if (game_state.board[newRow][newCol] == nullptr) {
             return true;
        }
    }
}

std::string King::getName() const {
    return (color == Color::White) ? "White Pawn" : "Black Pawn";
}
