#include "../header/GameState.h"
#include "../header/ChessPiece.h"
#include "../header/Pawn.h"
#include "../header/Rook.h"
#include "../header/Knight.h"
#include "../header/Bishop.h"
#include "../header/Queen.h"
#include "../header/King.h"
#include <iostream>


// Constructor implementation for GameEntity
GameEntity::GameEntity(std::string n, std::string t, std::string c)
    : name(n), type(t), color(c) {}

// Constructor for GameState
GameState::GameState() {
    current_player = "white";
    initialize_board();
}


// Function to set up the chess board
void GameState::initialize_board() {
    board = std::vector<std::vector<ChessPiece*>>(8, std::vector<ChessPiece*>(8, nullptr));
    
    // Place all pawns
    for (int i = 0; i < 8; ++i) {
        board[6][i] = new Pawn("white");
        board[1][i] = new Pawn("black");
    }

    place_major_pieces(7,"white"); // The function for this is below, starts on line 30 
    place_major_pieces(0, "black");
} 


// Function to place major pieces
void GameState::place_major_pieces(int row, const std::string& color) {
    // Place white major pieces
    board[row][0] = new Rook(color);
    board[row][1] = new Knight(color);
    board[row][2] = new Bishop(color);
    board[row][3] = new Queen(color);
    board[row][4] = new King(color);
    board[row][5] = new Bishop(color);
    board[row][6] = new Knight(color);
    board[row][7] = new Rook(color);

}


// Function to display the current board state
void GameState::display_board() {
    std::cout << "Current Board State:" << std::endl;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            ChessPiece* entity = board[row][col];
            if (entity->name != "") {
                std::cout << entity->color[0] << entity->name[0] << " ";  // Print color and piece type
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


void GameState::move_piece(int start_row, int start_col, int end_row, int end_col) {
    board[end_row][end_col] = board[start_row][start_col];
    board[start_row][start_col] = nullptr;
}

// Function to get the piece at a specific board position
//ChessPiece* GameState::get_piece_at(int row, int col) const {
//    return board[row][col];
//}


