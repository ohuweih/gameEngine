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

PieceType Pawn::getType() const {
    return PieceType::Pawn;
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

PieceType Rook::getType() const {
    return PieceType::Rook;
}


bool Knight::isValidMove(int newRow, int newCol, GameState& game_state) const {
    int rowDiff = std::abs(row - newRow);
    int colDiff = std::abs(col - newCol);
    Piece* targetPiece = game_state.board[newRow][newCol];

    // The L shape
    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff ==2)) {
        if (game_state.board[newRow][newCol] == nullptr) {
            return true;
        }
        else if (targetPiece->getColor() != color) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}


std::string Knight::getName() const {
    return (color == Color::White) ? "White Knight" : "Black Knight";
}

PieceType Knight::getType() const {
    return PieceType::Knight;
}


bool Bishop::isValidMove(int newRow, int newCol, GameState& game_state) const {
    Piece* targetPiece = game_state.board[newRow][newCol];

    if (std::abs(row - newRow) != std::abs(col - newCol)) {
        return false;
    }

    // Check if path is clear
    int rowStep = (row < newRow) ? 1 : -1;
    int colStep = (col < newCol) ? 1 : -1;
    int moveRow = row + rowStep;
    int moveCol = col + colStep;
    while (moveRow != newRow && moveCol != newCol) {
        if (game_state.board[moveRow][moveCol] != nullptr) {
            return false;
        }
        moveRow += rowStep;
        moveCol += colStep;
    }

    if (targetPiece == nullptr || targetPiece->getColor() != color) {
        return true;
    }
    
    return false;
}

std::string Bishop::getName() const {
    return (color == Color::White) ? "White Bishop" : "Black Bishop";
}

PieceType Bishop::getType() const {
    return PieceType::Bishop;
}


bool Queen::isValidMove(int newRow, int newCol, GameState& game_state) const {
    Rook tempRook(color, row, col);
    Bishop tempBishop(color, row, col);

    if (tempRook.isValidMove(newRow, newCol, game_state) ||
        tempBishop.isValidMove(newRow, newCol, game_state)) {
        return true;
    }

    return false;
}

std::string Queen::getName() const {
    return (color == Color::White) ? "White Queen" : "Black Queen";
}

PieceType Queen::getType() const {
    return PieceType::Queen;
}


bool King::isValidMove(int newRow, int newCol, GameState& game_state) const {
    int rowDiff = std::abs(row - newRow);
    int colDiff = std::abs(col - newCol);
    Piece* targetPiece = game_state.board[newRow][newCol];

    // Ensure the King moves only one square in any direction
    if (rowDiff <= 1 && colDiff <= 1) {
        // If the destination square is empty, it's a valid move
        if (targetPiece == nullptr) {
            return true;
        }
        // If there's an opponent's piece, it's a valid capture
        else if (targetPiece->getColor() != color) {
            return true;
        }
    }

    // Castle logic
    if (rowDiff == 0 && (colDiff == 2 || colDiff == -2)) {
        return SpecialState::canCastle(game_state, this, newCol);
        }

    // Invalid move
    return false;
}

std::string King::getName() const {
    return (color == Color::White) ? "White King" : "Black King";
}

PieceType King::getType() const {
    return PieceType::King;
}
