#include "../header/GameState.h"
#include <iostream>
#include <memory>

// Constructor for GameState
GameState::GameState()
    : board(8, std::vector<Piece*>(8, nullptr)),
      turnNumber(1)
{
    currentPlayer = "White";
    initialize_board();
}

//GameState::~GameState() {
//    for (auto& row : board) {
//        for (auto& piece : row){
//            delete piece;
//        }
//    }
//}

// Function to set up the chess board
void GameState::initialize_board() {

    // Place all pawns
    for (int i = 0; i < 8; ++i) {
        pieces.push_back(std::make_unique<Pawn>(Color::White, 6, i)); // Make unique Pawns
        board[6][i] = pieces.back().get();  // Store raw pointer to the piece on the board
        pieces.push_back(std::make_unique<Pawn>(Color::Black, 1, i));
        board[1][i] = pieces.back().get();
    }

    // Place major pieces
    place_major_pieces(7, Color::White);
    place_major_pieces(0, Color::Black);
}


// Function to place major pieces
void GameState::place_major_pieces(int row, Color color) {
    pieces.push_back(std::make_unique<Rook>(color, row, 0));
    board[row][0] = pieces.back().get();

    pieces.push_back(std::make_unique<Knight>(color, row, 1));
    board[row][1] = pieces.back().get();

    pieces.push_back(std::make_unique<Bishop>(color, row, 2));
    board[row][2] = pieces.back().get();

    pieces.push_back(std::make_unique<Queen>(color, row, 3));
    board[row][3] = pieces.back().get();

    pieces.push_back(std::make_unique<King>(color, row, 4));
    board[row][4] = pieces.back().get();

    pieces.push_back(std::make_unique<Bishop>(color, row, 5));
    board[row][5] = pieces.back().get();

    pieces.push_back(std::make_unique<Knight>(color, row, 6));
    board[row][6] = pieces.back().get();

    pieces.push_back(std::make_unique<Rook>(color, row, 7));
    board[row][7] = pieces.back().get();
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


// Move a piece form one location to another
void GameState::update_status(int newRow, int newCol, Piece* piece) {

    piece->logMove(newRow, newCol, turnNumber);
    turnNumber++;
    std::cout << "Analyzing piece moves...\n" << std::endl;
    analyzePieceMoves(piece);

    //Switch player
    currentPlayer = (currentPlayer == "White") ? "Black" : "White";
}

void GameState::analyzePieceMoves(const Piece* piece) {
    const std::vector<MoveEntry>& log = piece->getMovementLog();
    for (const MoveEntry& move : log) {
        std::cout << move.pieceName << " moved from (" << move.startRow << ", " << move.startCol << ") to ("
                  << move.endRow << ", " << move.endCol << ") on turn " << move.turnNumber << "\n";
    }
}


// Function to handle game logic (simulating user input)
//void GameState::update_game_logic(std::string& piece_name, std::string& action) {
//    std::cout << "It's " << current_player << "'s turn." << std::endl;
//    std::cout << "Choose a piece: ";
//    std::cin >> piece_name;
//
//    std::cout << "Choose an action: ";
//    std::cin >> action;
//
//    // Switch player
//    if (current_player == "White") {
//        current_player = "Black";
//    } else {
//        current_player = "White";
//    }
//}
