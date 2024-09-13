#include "Renderer.h"

// Constants for board size
const int TILE_SIZE = 75;  // Size of each square on the chessboard
const int BOARD_SIZE = 8;  // Chessboard is 8x8

// Function to render the chessboard
void render_chessboard(SDL_Renderer* renderer) {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            // Alternate between light and dark tiles
            if ((row + col) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Light color
            } else {
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);  // Dark color
            }
            SDL_Rect tile = {col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(renderer, &tile);  // Draw the tile
        }
    }
}

// Function to render chess pieces
void render_pieces(SDL_Renderer* renderer, const GameState& game_state) {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            GameEntity piece = game_state.get_piece_at(row, col);
            if (piece.name != "") {
                if (piece.color == "white") {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White pieces
                } else {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);        // Black pieces
                }
                // Draw a simple square to represent the piece
                SDL_Rect piece_rect = {col * TILE_SIZE + TILE_SIZE / 4, row * TILE_SIZE + TILE_SIZE / 4, TILE_SIZE / 2, TILE_SIZE / 2};
                SDL_RenderFillRect(renderer, &piece_rect);  // Simplified piece rendering (as a square)
            }
        }
    }
}
