#ifndef GAMESTATE_H  // Include guard to prevent multiple inclusion
#define GAMESTATE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "MoveEntry.h"
#include "SpecialState.h"
#include "Piece.h"


// Declaration of GameState class
class GameState {
    public:
        // Functions called from main cpp
        std::string currentPlayer;
        std::vector<std::vector<Piece*>> board;
        int turnNumber; 

        // Constructor
        GameState(); 
//        ~GameState(); //Destructor

        void initialize_board();
        void display_board() const;
        void update_status(int newRow, int newCol, Piece* piece);
//        void update_game_logic(std::string& piece_name, std::string& action);

    private:
        // Functions called with in the GameState cpp
        std::vector<std::unique_ptr<Piece>> pieces;
        void place_major_pieces(int row, Color color);
        void analyzePieceMoves(const Piece* piece);
};


#endif  // GAMESTATE_H
