#include "../header/GameState.h"
#include "../header/ChessPiece.h"
#include "../header/Pawn.h"
#include "../header/Rook.h"
#include "../header/Knight.h"
#include "../header/Bishop.h"
#include "../header/Queen.h"
#include "../header/King.h"
#include <iostream>
#include <memory>


// Constructor for GameState
GameState::GameState() {
    current_player = "white";
    initialize_board();
}


// Function to set up the chess board
void GameState::initialize_board() {
    board = std::vector<std::vector<std::unique_ptr<ChessPiece>>>(8, std::vector<std::unique_ptr<ChessPiece>>(8, nullptr));
    
    // Place all pawns
    for (int i = 0; i < 8; ++i) {
        board[6][i] = std::make_unique<Pawn>("white");
        board[1][i] = std::make_unique<Pawn>("black");
    }

    place_major_pieces(7,"white"); // The function for this is below, starts on line 30 
    place_major_pieces(0, "black");
} 


// Function to place major pieces
void GameState::place_major_pieces(int row, const std::string& color) {
    // Place white major pieces
    board[row][0] = std::make_unique<Rook>(color);
    board[row][1] = std::make_unique<Knight>(color);
    board[row][2] = std::make_unique<Bishop>(color);
    board[row][3] = std::make_unique<Queen>(color);
    board[row][4] = std::make_unique<King>(color);
    board[row][5] = std::make_unique<Bishop>(color);
    board[row][6] = std::make_unique<Knight>(color);
    board[row][7] = std::make_unique<Rook>(color);

}


// Function to display the current board state
void GameState::display_board() {
    std::cout << "Current Board State:" << std::endl;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            ChessPiece* entity = board[row][col].get();
            if (entity) {
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
    if (current_player == "white") {
        current_player = "black";
    } else {
        current_player = "white";
    }
}


void GameState::move_piece(int start_row, int start_col, int end_row, int end_col) {
    board[end_row][end_col] = std::move(board[start_row][start_col]);
    board[start_row][start_col].reset();
}

