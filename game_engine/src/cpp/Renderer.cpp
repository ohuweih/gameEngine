#include "../header/Renderer.h"

// Constants for board size
const int TILE_SIZE = 75;  // Size of each square on the chessboard
const int BOARD_SIZE = 8;  // Chessboard is 8x8

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

void render_pieces(SDL_Renderer* renderer, const GameState& game_state) {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            // Access the piece directly from the board using .get() on the unique_ptr
            Piece* piece = game_state.board[row][col];  // Assuming board is a 2D vector of std::unique_ptr<Piece>
            
            if (piece != nullptr) {  // Check if a piece exists on the current square
                if (piece->getColor() == Color::White) {  // Adjusted to use the Color enum
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Render white piece
                } else {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);        // Render black piece
                }
                
                // Render the piece as a simple square (you can expand this later to include textures)
                SDL_Rect piece_rect = {col * TILE_SIZE + TILE_SIZE / 4, row * TILE_SIZE + TILE_SIZE / 4, TILE_SIZE / 2, TILE_SIZE / 2};
                SDL_RenderFillRect(renderer, &piece_rect);  // Draw the piece as a square
            }
        }
    }
}

