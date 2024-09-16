#include <SDL2/SDL.h>
#include <iostream>
#include "header/GameState.h"
#include "header/Renderer.h"
#include "header/Input.h"

int main(int argc, char* argv[]) {
    // Initialize SDL with the video subsystem
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
    int selected_row = -1;
    int selected_col = -1;

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

                int row = mouse_y / 75;  // Assuming a 75x75 square grid for simplicity
                int col = mouse_x / 75;

                if (row >= 0 && row < 8 && col >= 0 && col < 8) {
                    if (!piece_selected) {
                        // Select a piece
                        Piece* piece = game_state.board[row][col];
                        if (piece) {  // Ensure there is a piece at this location
                            piece_selected = true;
                            selected_row = row;
                            selected_col = col;
							char pieceName = piece->getName();
							std::cout << "Piece selected: " << pieceName << std::endl;
                        }
                    } else {
                        // Move the selected piece
                        Piece* selected_piece = game_state.board[selected_row][selected_col];
                        if (selected_piece && selected_piece->move(selected_row, selected_col, row, col, game_state.board)) {
                            game_state.board[row][col] = game_state.board[selected_row][selected_col];// this is how we move pieces
                            game_state.board[selected_row][selected_col] = nullptr; // Clear the old square
                        } else {
                            std::cout << "Invalid move!" << std::endl;
                        }

                        // Reset selection
                        piece_selected = false;
                    }
                }
            }
        }

        // Render chessboard and pieces
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        render_chessboard(renderer);  // Assuming this function is implemented
        render_pieces(renderer, game_state);  // Assuming this function is implemented

        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

