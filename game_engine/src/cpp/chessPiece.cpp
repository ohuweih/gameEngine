#include "../header/GameState.h"
#include <iostream>
#include <memory>

// Piece logic
bool Pawn::move(int start_row, int start_col, int end_row, int end_col, const std::vector<std::vector<Piece*>>& board) {
    int direction = (color == Color::White) ? -1 : 1; // White moves up, Black moves down
    // Ensure we are within the bounds of the game_state.board
    if (end_row < 0 || end_row >= 8 || end_col < 0 || end_col >= 8) {
        return false;
    }

    // Pawn forward move
    if (start_col == end_col && board[end_row][end_col] == nullptr) {
        if (end_row == start_row + direction) {
            return true; // Move forward one space
        }
        // Two-space move at the start
        if ((color == Color::White && start_row == 6 && end_row == 4 && board[5][end_col] == nullptr) ||
            (color == Color::Black && start_row == 1 && end_row == 3 && board[2][end_col] == nullptr)) {
            return true; // Two-space move from starting position
        }
    }

    // Pawn Capture
    if (std::abs(start_col - end_col) == 1 && end_row == start_row + direction) {
        if (board[end_row][end_col] && board[end_row][end_col]->getColor() != color) {
            return true;
        }
    }

    return false;
}

char Pawn::getName() const {
    return 'P';
}


bool Rook::move(int start_row, int start_col, int end_row, int end_col, const std::vector<std::vector<Piece*>>& board) {
    if (start_row != end_row && start_col != end_col) {
            return false;
    }

    //check if path is clear
    if (start_row == end_row) {
        int step = (start_col < end_col) ? 1 : -1;
        for (int col = start_col + step; col != end_col; col += step) {
            if (board[start_row][col]) return false; //Blocked
        }
    } else {
        int step = (start_row < end_row) ? 1 : -1;
        for (int row = start_row + step; row != end_row; row += step) {
            if (board[row][start_col]) return false; //Blocked again
        }
    }

    return true;
}

char Rook::getName() const {
    return 'R';
}


bool Knight::move(int start_row, int start_col, int end_row, int end_col, const std::vector<std::vector<Piece*>>& board) {
    int row_diff = std::abs(start_row - end_row);
    int col_diff = std::abs(start_col - end_col);

    // The L shape
    if ((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)) {
        return true;
    }

    return false;
}

char Knight::getName() const {
        return 'N';
}


bool Bishop::move(int start_row, int start_col, int end_row, int end_col, const std::vector<std::vector<Piece*>>& board) {
    if (std::abs(start_row - end_row) != std::abs(start_col - end_col)) {
            return false; // This is the diagonal move
    }

    // Check if path is clear
    int row_step = (start_row < end_row) ? 1 : -1;
    int col_step = (start_col < end_col) ? 1 : -1;
    int row = start_row + row_step;
    int col = start_col + col_step;
    while (row != end_row && col != end_col) {
        if (board[row][col]) return false; // Blocked
        row += row_step;
        col += col_step;
    }

    return true;
}

char Bishop::getName() const {
    return 'B';
}


bool Queen::move(int start_row, int start_col, int end_row, int end_col, const std::vector<std::vector<Piece*>>& board) {
    // A queen can move like either a rook or a bishop
    Rook temp_rook(color);       // Create a temporary Rook with the same color as the Queen
    Bishop temp_bishop(color);   // Create a temporary Bishop with the same color as the Queen

    // Check if the move is valid as a Rook or as a Bishop
    if (temp_rook.move(start_row, start_col, end_row, end_col, board) ||
        temp_bishop.move(start_row, start_col, end_row, end_col, board)) {
        return true;
    }

    return false;
}

char Queen::getName() const {
    return 'Q';
}


bool King::move(int start_row, int start_col, int end_row, int end_col, const std::vector<std::vector<Piece*>>& board) {
    int row_diff = std::abs(start_row - end_row);
    int col_diff = std::abs(start_col - end_col);

    // Check if the king moves exactly one square in any direction
    if (row_diff <= 1 && col_diff <= 1) {
        return true;  // Valid move
    } else {
        return false;  // Invalid move
    }
}

char King::getName() const {
    return 'K';
}
