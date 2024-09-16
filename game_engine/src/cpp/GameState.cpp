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
