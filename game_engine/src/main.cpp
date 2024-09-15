#include <SDL2/SDL.h>
#include <iostream>
#include "header/GameState.h"
#include "header/Renderer.h"
#include "header/Input.h"
#include "header/ChessPiece.h"
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


    //Track selected piece
    bool piece_selected = false;
    int selected_row = -1;
    int selected_col = -1;


    while (isRunning) {
        // Poll for events (like window close) and process them
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false; // Exit the loop when the window is closed
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Get mouse click coordinates
                int mouse_x, mouse_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);


                int row,col;
                if (get_board_coordinates(mouse_x, mouse_y, row, col)) {
                    if (!piece_selected) {
                        // Select a piece
                        ChessPiece* piece = game_state.get_piece_at(row, col);
                        if (piece && piece-> name != "") { // Using -> for accessing class members
                            piece_selected = true;
                            selected_row = row;
                            selected_col = col;
                        }
                    } else {
                        // Valid move logic here
                        ChessPiece* selected_piece = game_state.get_piece_at(selected_row, selected_col);
                        if (selected_piece && selected_piece->is_valid_move(game_state, selected_row, selected_col, row, col)) {
                        // Move the selected piece to the new position
                            game_state.move_piece(selected_row, selected_col, row, col);
                        } else {
                            std::cout << "Invalid move for " << selected_piece->name << " from (" << selected_row << "," << selected_col << ") to (" << row << "," << col << ")!" << std::endl;

                        }

                        // Reset selection
                        piece_selected = false;
                    }
                }
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
