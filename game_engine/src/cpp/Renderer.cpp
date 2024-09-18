#include "../header/Renderer.h"

// Constants for board size
const int BOARD_SIZE = 8;  // Chessboard is 8x8
const int TILE_SIZE = 75;

// Function to render the chessboard
void render_chessboard(SDL_Renderer* renderer) {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            // Alternate between light and dark tiles
            if ((row + col) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);  // Light color
            } else {
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);  // Dark color
            }
            SDL_Rect tile = {col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(renderer, &tile);  // Draw the tile
        }
    }
}

// Function to render the pieces
void render_pieces(SDL_Renderer* renderer, const GameState& game_state) {
    // Render white pieces
    for (const auto& piece : game_state.wp) {
        render_piece(renderer, piece.get());  // Render each white piece
    }

    // Render black pieces
    for (const auto& piece : game_state.bp) {
        render_piece(renderer, piece.get());  // Render each black piece
    }
}

// Helper function to render an individual piece
void render_piece(SDL_Renderer* renderer, const Piece* piece) {
    if (piece == nullptr) return;

    // Set the color based on the piece's color
    if (piece->getColor() == Color::White) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Render white piece
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);        // Render black piece
    }

    // Use the piece's row and col to calculate its position on the board
    int row = piece->getRow();
    int col = piece->getCol();

    // Render the piece as a simple square (you can replace this with textures if needed)
    SDL_Rect piece_rect = {
        col * TILE_SIZE + TILE_SIZE / 4,  // X position
        row * TILE_SIZE + TILE_SIZE / 4,  // Y position
        TILE_SIZE / 2,                    // Width
        TILE_SIZE / 2                     // Height
    };
    SDL_RenderFillRect(renderer, &piece_rect);  // Draw the piece as a square
}
