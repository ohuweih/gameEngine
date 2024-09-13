#include "../header/GameState.h"
#include <iostream>


// Constructor implementation for GameEntity
GameEntity::GameEntity(std::string n, std::string t, std::string c)
    : name(n), type(t), color(c) {}

// Constructor for GameState
GameState::GameState() {
    current_player = "White";
    initialize_board();
}


// Function to set up the chess board
void GameState::initialize_board() {
    board = std::vector<std::vector<GameEntity>>(8, std::vector<GameEntity>(8, GameEntity("", "empty", "")));
    
    // Place all pawns
    for (int i = 0; i < 8; ++i) {
        board[1][i] = GameEntity("Pawn", "piece", "white");
        board[6][i] = GameEntity("Pawn", "piece", "black");
    }

    place_major_pieces(0,"white"); // The function for this is below, starts on line 30 
    place_major_pieces(7, "black");
}


// Function to place major pieces
void GameState::place_major_pieces(int row, const std::string& color) {
    // Place white major pieces
    board[row][0] = GameEntity("Rook", "piece", color);
    board[row][1] = GameEntity("Knight", "piece", color);
    board[row][2] = GameEntity("Bishop", "piece", color);
    board[row][3] = GameEntity("Queen", "piece", color);
    board[row][4] = GameEntity("King", "piece", color);
    board[row][5] = GameEntity("Bishop", "piece", color);
    board[row][6] = GameEntity("Knight", "piece", color);
    board[row][7] = GameEntity("Rook", "piece", color);

}


// validate a move based on miece movement rules
bool GameState::is_valid_move(int start_row, int start_col, int end_row, int end_col) {
    GameEntity piece = board[start_row][start_col];
    if (piece.name == "") {
        std::cout << "No piece at the selected position!" << std::endl;
        return false;
    }

    if (piece.name == "Pawn") {
        return is_valid_pawn_move(start_row, start_col, end_row, end_col, piece.color);
    } else if (piece.name == "Rook") {
        return is_valid_rook_move(start_row, start_col, end_row, end_col);
    } else if (piece.name == "Knight") {
        return is_valid_knight_move(start_row, start_col, end_row, end_col);
    } else if (piece.name == "Bishop") {
        return is_valid_bishop_move(start_row, start_col, end_row, end_col);
    } else if (piece.name == "Queen") {
        return is_valid_queen_move(start_row, start_col, end_row, end_col);
    } else if (piece.name == "King") {
        return is_valid_king_move(start_row, start_col, end_row, end_col);
    }

    return false;
}


// Function for valid or invalid move. This should be broke later in the game for the crazy part of the game
bool GameState::is_valid_pawn_move(int start_row, int start_col, int end_row, int end_col, const std::string& color) {
    int direction = (color == "white") ? -1 : 1; // This should make white move up and black move down... Hopefuly lol


    //Pawn move
    if (start_col == end_col && board[end_row][end_col].name == "") {
        if (end_row == start_row + direction) return true; // Move forward
        if ((color == "white" && start_row ==6 && end_row ==4) ||
                (color == "black" && start_row ==1 && end_row ==3)) {
            return true; // Pawn two space start move
        }
    }


    // Pawn Capture
    if (std::abs(start_col - end_col) == 1 && end_row == start_row + direction) {
            if (board[end_row][end_col].name != "" && board[end_row][end_col].color != color) {
            return true;
            }
    }

    return false;
}


// Rook move
bool GameState::is_valid_rook_move(int start_row, int start_col, int end_row, int end_col) {
    if (start_row != end_row && start_col != end_col) {
            return false;
    }

    //check if path is clear
    if (start_row == end_row) {
        int step = (start_col < end_col) ? 1 : -1;
        for (int col = start_col + step; col != end_col; col += step) {
            if (board[start_row][col].name != "") return false; //Blocked
        }
    } else {
        int step = (start_row < end_row) ? 1 : -1;
        for (int row = start_row + step; row != end_row; row += step) {
            if (board[row][start_col].name != "") return false; //Blocked again
        }
    }

    return true;
}


// knight move
bool GameState::is_valid_knight_move(int start_row, int start_col, int end_row, int end_col) {
    int row_diff = std::abs(start_row - end_row);
    int col_diff = std::abs(start_col - end_col);

    // The L shape
    if ((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)) {
        return true;
    }

    return false;
}


// bishop move
bool GameState::is_valid_bishop_move(int start_row, int start_col, int end_row, int end_col) {
    if (std::abs(start_row - end_row) != std::abs(start_col - end_col)) {
            return false; // This is the diagonal move
    }

    // Check if path is clear
    int row_step = (start_row < end_row) ? 1 : -1;
    int col_step = (start_col < end_col) ? 1 : -1;
    int row = start_row + row_step;
    int col = start_col + col_step;
    while (row != end_row && col != end_col) {
        if (board[row][col].name != "") return false; // Blocked
        row += row_step;
        col += col_step;
    }

    return true;
}


// Queen move (call rook and bishop functions)
bool GameState::is_valid_queen_move(int start_row, int start_col, int end_row, int end_col) {
    return is_valid_rook_move(start_row, start_col, end_row, end_col) ||
           is_valid_bishop_move(start_row, start_col, end_row, end_col);
}


// King move
bool GameState::is_valid_king_move(int start_row, int start_col, int end_row, int end_col) {
    int row_diff = std::abs(start_row - end_row);
    int col_diff = std::abs(start_col - end_col);

    // any direction movement
    if (row_diff <= 1 && col_diff <=1) {
        return true;
    }

    return false;
}


// Function to display the current board state
void GameState::display_board() {
    std::cout << "Current Board State:" << std::endl;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            GameEntity& entity = board[row][col];
            if (entity.name != "") {
                std::cout << entity.color[0] << entity.name[0] << " ";  // Print color and piece type
            } else {
                std::cout << "-- ";
            }
        }
        std::cout << std::endl;
    }
}


// Function to handle game logic (simulating user input)
void GameState::update_game_logic(std::string& piece_name, std::string& action) {
    std::cout << "It's " << current_player << "'s turn." << std::endl;
    std::cout << "Choose a piece: ";
    std::cin >> piece_name;

    std::cout << "Choose an action: ";
    std::cin >> action;

    // Switch player
    if (current_player == "White") {
        current_player = "Black";
    } else {
        current_player = "White";
    }
}


// Function to get the piece at a specific board position
GameEntity GameState::get_piece_at(int row, int col) const {
    return board[row][col];
}

