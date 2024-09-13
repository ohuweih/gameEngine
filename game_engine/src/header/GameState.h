#ifndef GAMESTATE_H  // Include guard to prevent multiple inclusion
#define GAMESTATE_H

#include <iostream>
#include <string>
#include <vector>


// Declaration of Game Entity class
class GameEntity {
    public:
        std::string name;
        std::string type;
        std::string color;

        // Constructor
        GameEntity(std::string n = "", std::string t = "empty", std::string c = "");
};


// Declaration of GameState class
class GameState {
    public:
        std::string current_player;
        std::vector<std::vector<GameEntity>> board;


        // Constructor
        GameState();


        // Function to initialize the chess board
        void initialize_board();


        // Functtion to place major pieces
        void place_major_pieces(int row, const std::string& color);


        // Function to display the chess board in the console (for debugging)
        void display_board();

        
        // Function for pawn movement
        bool is_valid_move(int start_row, int start_col, int end_row, int end_col);


        // Function to handle game logic (e.g., updating turns, selecting pieces)
        void update_game_logic(std::string& piece_name, std::string& action);


        // Function to get the piece at a specific board position
        GameEntity get_piece_at(int row, int col) const;
};


#endif  // GAMESTATE_H
