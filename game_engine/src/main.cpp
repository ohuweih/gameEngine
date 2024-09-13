#include <SDL2/SDL.h>
#include <iostream>
#include "GameState.h"

// Constants for board size
const int TILE_SIZE = 75; // Size of each square on the chessboard
const int BOARD_SIZE = 8; // board is 8*8

// Function to render the chessboard (This can be replace or modified with an img for the board)
void render_chessboard(SDL_Renderer* renderer) {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            // Alternate between light and dark tiles
            if ((row + col) %2 == 0) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //light color
            } else {
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); //dark color
            }
            SDL_Rect tile = {col *  TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(renderer, &tile); // Draw the tile
        }
    }
}


// Function to render the chess pieces
void render_pieces(SDL_Renderer* renderer, const GameState& game_state) {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col <BOARD_SIZE; ++col) {
            GameEntity piece = game_state.get_piece_at(row, col);
            if (piece.name != "") {
                if (piece.color == "white") {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white pieces
                } else {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black pieces
                }
                // Draw a simple circle or square
                SDL_Rect piece_rect = {col * TILE_SIZE + TILE_SIZE / 4, row * TILE_SIZE + TILE_SIZE / 4, TILE_SIZE / 2, TILE_SIZE /2 };
                SDL_RenderFillRect(renderer, &piece_rect);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Initialize SDL with video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Failed to initialize SDL: "<<SDL_GetError() << std::endl;
		return -1;
	}

    // Create an SDL window with title centered
    SDL_Window* window = SDL_CreateWindow(
        "Game Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);
    // Check if the window creation failed, print error
    if (!window) {
        std::cerr << "Filed to create window: " << SDL_GetError() << std::endl;
        return -1;
    }
    
    // Create a renderer for the window, using hardware acceleration
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // check if the renderer creation failed, print error, clean up window and exit if it did
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return -1;
    }

    // Initialize Game
    GameState game_state;


    // Main game loop flag to check if the program is running
    bool isRunning = true;
    SDL_Event event; // SDL event to handle user input
    while (isRunning) {
        // Poll for events (like window close) and process them
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false; // Exit the loop when the window is closed
            }
        }

        // set the color for the renderer - in this case black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        //clear the current window content and set it to the background color
        SDL_RenderClear(renderer);

        // Rendering logic will go here. drawing pieces, board, etc.
        render_chessboard(renderer);
        render_pieces(renderer, game_state);
        
        // Preset the rendered content to the window
        SDL_RenderPresent(renderer);
    }

    // Clean up resources after the loop ends
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); // Shut down SDL subsystems
    return 0;
}
