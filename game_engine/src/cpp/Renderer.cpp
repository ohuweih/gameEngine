#include "../header/Renderer.h"

// Constants for board size
const int BOARD_SIZE = 8;  // Chessboard is 8x8
const int TILE_SIZE = 75;  // Size of each tile on the board

// Function to render the chessboard
void render_chessboard(SDL_Renderer* renderer) {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            // Alternate between light and dark tiles
            if ((row + col) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);  // Light tile color
            } else {
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);  // Dark tile color
            }
            SDL_Rect tile = {col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(renderer, &tile);  // Draw the tile
        }
    }
}

// Function to render the pieces based on the board
void render_pieces(SDL_Renderer* renderer, const GameState& game_state) {
    // Loop through the board and render each piece
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            Piece* piece = game_state.board[row][col];  // Get the piece at the current position
            if (piece != nullptr) {
                render_piece(renderer, piece);  // Render the piece if it exists
            }
        }
    }
}

// Helper function to render an individual piece
void render_piece(SDL_Renderer* renderer, const Piece* piece) {
    if (piece == nullptr) return;  // Skip rendering if no piece

    // Set the color based on the piece's color
    if (piece->getColor() == Color::White) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Render white piece
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);        // Render black piece
    }

    // Calculate the position of the piece on the board
    int row = piece->getRow();
    int col = piece->getCol();

    // Render the piece as a simple square (can be replaced with textures in the future)
    SDL_Rect piece_rect = {
        col * TILE_SIZE + TILE_SIZE / 4,  // X position
        row * TILE_SIZE + TILE_SIZE / 4,  // Y position
        TILE_SIZE / 2,                    // Width
        TILE_SIZE / 2                     // Height
    };
    SDL_RenderFillRect(renderer, &piece_rect);  // Draw the piece as a square
}
