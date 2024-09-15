#ifndef GAMESTATE_H  // Include guard to prevent multiple inclusion
#define GAMESTATE_H

#include <iostream>
#include <string>
#include <vector>
#include "ChessPiece.h"

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
        // Functions called from main cpp
        std::string current_player;
        std::vector<std::vector<ChessPiece*>> board;


        //Track whether the king or rook have moved for castling
        bool white_king_moved = false;
        bool white_rook_king_side_moved = false;
        bool white_rook_queen_side_moved = false;


        bool black_king_moved = false;
        bool black_rook_king_side_moved = false;
        bool black_rook_queen_side_moved = false;


        // Constructor
        GameState();


        // Function to initialize the chess board
        void initialize_board();


        ChessPiece* get_piece_at(int row, int col) const {
            return board[row][col];
        }

		void move_piece(int start_row, int start_col, int end_row, int end_col);

        // Function to display the chess board in the console (for debugging)
        void display_board();

        
        // Function to handle game logic (e.g., updating turns, selecting pieces)
        void update_game_logic(std::string& piece_name, std::string& action);

    private:
        // Functions called with in the GameState cpp
    	void place_major_pieces(int row, const std::string& color);
    
};


#endif  // GAMESTATE_H
