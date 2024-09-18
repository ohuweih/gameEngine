#include <SDL2/SDL.h>
#include <iostream>
#include "header/GameState.h"
#include "header/Renderer.h"
#include "header/Input.h"

int main(int argc, char* argv[]) {
    // Initialize SDL
    const int TILE_SIZE = 75;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow(
        "Chess Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create an SDL renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return -1;
    }

    // Initialize game state
    GameState game_state;

    // Main game loop flag
    bool isRunning = true;
    SDL_Event event;

    // Track selected piece
    bool piece_selected = false;
    Piece* selected_piece = nullptr;

    // Main game loop
    while (isRunning) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Get mouse click coordinates
                int mouse_x, mouse_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);

                int row = mouse_y / TILE_SIZE;  // Assuming a 75x75 square grid for simplicity
                int col = mouse_x / TILE_SIZE;

                if (row >= 0 && row < 8 && col >= 0 && col < 8) {
                    if (!piece_selected) {
                        // Select a piece from the game state's pieces
                        selected_piece = game_state.get_piece_at(row, col);
                        if (selected_piece) {
                            piece_selected = true;
                            std::cout << "Piece selected: " << selected_piece->getName() << std::endl;
                        }
                    } else {
                        // Move the selected piece
                        if (selected_piece->isValidMove(row, col, game_state)) {
                            selected_piece->move(row, col);
                            std::cout << "Piece moved to: (" << row << ", " << col << ")" << std::endl;
                        } else {
                            std::cout << "Invalid move!" << std::endl;
                        }

                        // Reset selection
                        piece_selected = false;
                        selected_piece = nullptr;
                    }
                }
            }
        }

        // Render chessboard and pieces
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        render_chessboard(renderer);  // Renders the chessboard
        render_pieces(renderer, game_state);  // Renders the chess pieces

        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

