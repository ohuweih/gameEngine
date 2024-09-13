
#include "GameState.h"
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
    
    // Place white pawns
    for (int i = 0; i < 8; ++i) {
        board[1][i] = GameEntity("Pawn", "piece", "white");
    }

    // Place Black pawns
    for (int i = 0; i < 8; ++i) {
        board[6][i] = GameEntity("Pawn", "piece", "black");
    }

    // Place white major pieces
    board[0][0] = GameEntity("Rook", "piece", "white");
    board[0][1] = GameEntity("Knight", "piece", "white");
    board[0][2] = GameEntity("Bishop", "piece", "white");
    board[0][3] = GameEntity("Queen", "piece", "white");
    board[0][4] = GameEntity("King", "piece", "white");
    board[0][5] = GameEntity("Bishop", "piece", "white");
    board[0][6] = GameEntity("Knight", "piece", "white");
    board[0][7] = GameEntity("Rook", "piece", "white");

    // Place black major pieces
    board[7][0] = GameEntity("Rook", "piece", "black");
    board[7][1] = GameEntity("Knight", "piece", "black");
    board[7][2] = GameEntity("Bishop", "piece", "black");
    board[7][3] = GameEntity("Queen", "piece", "black");
    board[7][4] = GameEntity("King", "piece", "black");
    board[7][5] = GameEntity("Bishop", "piece", "black");
    board[7][6] = GameEntity("Knight", "piece", "black");
    board[7][7] = GameEntity("Rook", "piece", "black");
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

