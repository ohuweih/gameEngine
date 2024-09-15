#include "../header/PieceMovement.h"
#include <iostream>


// validate a move based on miece movement rules
bool PieceMovement::is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) {
    GameEntity piece = game_state.board[start_row][start_col];
    GameEntity target_piece = game_state.get_piece_at(end_row, end_col);
    if (piece.name == "") {
        std::cout << "No piece at the selected position!" << std::endl;
        return false;
    }

    
    // Ensure that a piece cannot capture a piece of the same color
    bool capture_own_piece = false; 
    if (capture_own_piece == false) {
        if (target_piece.name != "" && target_piece.color == piece.color) {
            std::cout << "Cannot capture your own piece!" << std::endl;
            return false;
        }
    }


    if (piece.name == "Pawn") {
        return is_valid_pawn_move(game_state, start_row, start_col, end_row, end_col, piece.color);
    } else if (piece.name == "Rook") {
        return is_valid_rook_move(game_state, start_row, start_col, end_row, end_col);
    } else if (piece.name == "Knight") {
        return is_valid_knight_move(game_state, start_row, start_col, end_row, end_col);
    } else if (piece.name == "Bishop") {
        return is_valid_bishop_move(game_state, start_row, start_col, end_row, end_col);
    } else if (piece.name == "Queen") {
        return is_valid_queen_move(game_state, start_row, start_col, end_row, end_col);
    } else if (piece.name == "King") {
        return is_valid_king_move(game_state, start_row, start_col, end_row, end_col);
    }

    return false;
}


// Function for valid or invalid move. This should be broke later in the game for the crazy part of the game
bool PieceMovement::is_valid_pawn_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col, const std::string& color) {
    int direction = (color == "white") ? -1 : 1; // This should make white move up and black move down... Hopefuly lol

    // Ensure the we are with in the bounds of the game_state.board
    if (end_row < 0 || end_row > 7 || end_col < 0 || end_col > 7){
        return false;
    }


    //Pawn move
    if (start_col == end_col && game_state.board[end_row][end_col].name == "") {
        if (end_row == start_row + direction) {
            return true; // Move forward
        }


        if ((color == "white" && start_row == 6 && end_row == 4 && game_state.board[5][end_col].name == "" ) ||
            (color == "black" && start_row == 1 && end_row == 3 && game_state.board[2][end_col].name =="" )) {
            return true; // Pawn two space start move if both spaces are clear.
        }
    }


    // Pawn Capture
    if (std::abs(start_col - end_col) == 1 && end_row == start_row + direction) {
        if (game_state.board[end_row][end_col].name != "" && game_state.board[end_row][end_col].color != color) {
            return true;
        }
    }

    return false;
}


// Rook move
bool PieceMovement::is_valid_rook_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) {
    if (start_row != end_row && start_col != end_col) {
            return false;
    }

    //check if path is clear
    if (start_row == end_row) {
        int step = (start_col < end_col) ? 1 : -1;
        for (int col = start_col + step; col != end_col; col += step) {
            if (game_state.board[start_row][col].name != "") return false; //Blocked
        }
    } else {
        int step = (start_row < end_row) ? 1 : -1;
        for (int row = start_row + step; row != end_row; row += step) {
            if (game_state.board[row][start_col].name != "") return false; //Blocked again
        }
    }

    return true;
}


// knight move
bool PieceMovement::is_valid_knight_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) {
    int row_diff = std::abs(start_row - end_row);
    int col_diff = std::abs(start_col - end_col);

    // The L shape
    if ((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)) {
        return true;
    }

    return false;
}


// bishop move
bool PieceMovement::is_valid_bishop_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) {
    if (std::abs(start_row - end_row) != std::abs(start_col - end_col)) {
            return false; // This is the diagonal move
    }

    // Check if path is clear
    int row_step = (start_row < end_row) ? 1 : -1;
    int col_step = (start_col < end_col) ? 1 : -1;
    int row = start_row + row_step;
    int col = start_col + col_step;
    while (row != end_row && col != end_col) {
        if (game_state.board[row][col].name != "") return false; // Blocked
        row += row_step;
        col += col_step;
    }

    return true;
}


// Queen move (call rook and bishop functions)
bool PieceMovement::is_valid_queen_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) {
    return is_valid_rook_move(game_state, start_row, start_col, end_row, end_col) ||
           is_valid_bishop_move(game_state, start_row, start_col, end_row, end_col);
}


// King move
bool PieceMovement::is_valid_king_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) {
    int row_diff = std::abs(start_row - end_row);
    int col_diff = std::abs(start_col - end_col);

    // any direction movement
    if (row_diff <= 1 && col_diff <=1) {
        return true;
    }

    return false;
}
