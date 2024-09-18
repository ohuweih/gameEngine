#include "../header/GameState.h"

// Constructor for GameState
GameState::GameState() {
    current_player = "White";
    initialize_pieces();
}

void GameState::initialize_pieces() {
    // Initialize Pawns pieces
    for (int i = 0; i < 8; ++i) {
        wp.push_back(std::make_unique<Pawn>(Color::White, 6, i));
        bp.push_back(std::make_unique<Pawn>(Color::Black, 1, i));
    }
    wp.push_back(std::make_unique<Rook>(Color::White, 7, 0));
    wp.push_back(std::make_unique<Knight>(Color::White, 7, 1));
    wp.push_back(std::make_unique<Bishop>(Color::White, 7, 2));
    wp.push_back(std::make_unique<Queen>(Color::White, 7, 3));
    wp.push_back(std::make_unique<King>(Color::White, 7, 4));
    wp.push_back(std::make_unique<Bishop>(Color::White, 7, 5));
    wp.push_back(std::make_unique<Knight>(Color::White, 7, 6));
    wp.push_back(std::make_unique<Rook>(Color::White, 7, 7));

	bp.push_back(std::make_unique<Rook>(Color::Black, 0, 0));
    bp.push_back(std::make_unique<Knight>(Color::Black, 0, 1));
    bp.push_back(std::make_unique<Bishop>(Color::Black, 0, 2));
    bp.push_back(std::make_unique<Queen>(Color::Black, 0, 3));
    bp.push_back(std::make_unique<King>(Color::Black, 0, 4));
    bp.push_back(std::make_unique<Bishop>(Color::Black, 0, 5));
    bp.push_back(std::make_unique<Knight>(Color::Black, 0, 6));
    bp.push_back(std::make_unique<Rook>(Color::Black, 0, 7));
}


// Function to display the current board state
void GameState::display_board() const {
    std::cout << "Current Board State:" << std::endl;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            bool found_piece = false;
            for (const auto& piece : wp) {
                if (piece->getRow() == row && piece->getCol() == col) {
                    std::cout << piece->getName() << " ";
                    found_piece = true;
                    break;
                }
            }
            if (!found_piece) {
                for (const auto& piece : bp) {
                    if (piece->getRow() == row && piece->getCol() == col) {
                        std::cout << piece->getName() << " ";
                        found_piece = true;
                        break;
                    }
                }
            }
            if (!found_piece) {
                std::cout << ". "; // Empty Square
            }
        }
        std::cout << std::endl;
    }
}


// Function to handle game logic (simulating user input)
void GameState::update_game_logic(std::string& piece_name, std::string& action) {
    Piece* selected_piece = nullptr;
    
    // Find the piece for the active player
    auto& current_pieces = (current_player == "White" ? wp : bp);
    for (const auto& piece : current_pieces) {
        if (piece->getName() == piece_name) {
            selected_piece = piece.get();
            break;
        }
    }

    if (selected_piece) {
        int newRow, newCol;
        std::cout << "Enter new roe and column: ";
        std::cin >> newRow >> newCol;

        if (selected_piece->isValidMove(newRow, newCol, *this)) {
            selected_piece->move(newRow, newCol);
        } else {
            std::cout << "Invalid move for " << piece_name << std::endl;
        }
    }

    // Switch player
    current_player = (current_player =="white") ? "Black" : "White";
}

Piece* GameState::get_piece_at(int row, int col) const {
    for (const auto& piece : wp) {
        if (piece->getRow() == row && piece->getCol() == col) {
            return piece.get();
        }
    }
    for (const auto& piece : bp) {
        if (piece->getRow() == row && piece->getCol() == col) {
            return piece.get();
        }
    }
    return nullptr;  // No piece found at the given position
}


void GameState::remove_piece_from_board(int row, int col, std::vector<std::unique_ptr<Piece>>& pieces) {
    auto it = std::remove_if(pieces.begin(), pieces.end(), [row, col](const std::unique_ptr<Piece>& piece) {
        return piece->getRow() == row && piece->getCol() == col;
    });
    pieces.erase(it, pieces.end());  // Erase the removed piece
}
