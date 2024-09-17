#include "../header/GameState.h"
#include <iostream>
#include <memory>

// Constructor for GameState
GameState::GameState()
    : board(8, std::vector<Piece*>(8, nullptr))
{
    current_player = "White";
    initialize_board();
}

GameState::~GameState() {
    for (auto& row : board) {
        for (auto& piece : row){
            delete piece;
        }
    }
}

// Function to set up the chess board
void GameState::initialize_board() {

    // Place all pawns
    for (int i = 0; i < 8; ++i) {
        board[6][i] = new Pawn(Color::White);
        board[1][i] = new Pawn(Color::Black);
    }

    // Place major pieces
    place_major_pieces(7, "White");
    place_major_pieces(0, "Black");
}


// Function to place major pieces
void GameState::place_major_pieces(int row, const std::string& color) {
    Color piece_color;

    if (color == "White") {
        piece_color = Color::White;
    } else if (color == "Black") {
        piece_color = Color::Black;
    } else {
        std::cerr << "Invalid color : " << color << std::endl;
        return; // Exit if color is invalid
    }

    board[row][0] = new Rook(piece_color);
    board[row][1] = new Knight(piece_color);
    board[row][2] = new Bishop(piece_color);
    board[row][3] = new Queen(piece_color);
    board[row][4] = new King(piece_color);
    board[row][5] = new Bishop(piece_color);
    board[row][6] = new Knight(piece_color);
    board[row][7] = new Rook(piece_color);
}


// Function to display the current board state
void GameState::display_board() const {
    std::cout << "Current Board State:" << std::endl;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col]) {
                std::cout << board[row][col]->getName() << " ";  // Display piece symbol
            } else {
                std::cout << ". "; //Empty Square
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


// Function to move pieces using std::move()
//bool GameState::move_piece(int start_row, int start_col, int end_row, int end_col) {
//    if(!board[start_row][start_col]) { 
//        std::cout << "No piece at the start position!" << std::endl;
//        return false; // No piece to move
//    }
//
    // Perform move and transfer ownership using std::move
//    if (board[start_row][start_col]->move(start_row, start_col, end_row, end_col, board)) {
//        board[end_row][end_col] = std::move(board[start_row][start_col]); // Move Piece
//        board[start_row][start_col] = nullptr; // Empty the starting position
//        return true;
//    } else {
//        std::cout << "Invalid move!" << std::endl;
//        return false;
//    }
//}
