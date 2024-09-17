#ifndef GAMESTATE_H  // Include guard to prevent multiple inclusion
#define GAMESTATE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

enum class Color{
    White,
    Black
};


class Piece {
    protected:
        Color color; // The color of the piece


    public:
        Piece(Color c) : color(c){}

        virtual ~Piece() = default;
        virtual bool move(int start_row, int start_col, int end_row, int end_col, const std::vector<std::vector<Piece*>>& board) = 0; // "common" method for all pieces This is a pure virtual placeholder
        virtual char getName() const = 0; // Each piece can have its own name
        Color getColor() const { return color; } 
};


class Pawn : public Piece {
    public:
        Pawn(Color c) : Piece(c) {}
        bool move(int start_row, int start_col, int end_row, int end_col, const std::vector<std::vector<Piece*>>& board) override;
        char getName() const override;
};


class Rook : public Piece {
    public:
        Rook(Color c) : Piece(c) {}
        bool move(int start_row, int start_col, int end_row, int end_col, const std::vector<std::vector<Piece*>>& board) override;  // Declaration of the move function
        char getName() const override;  // Declaration of getName
};


class Knight : public Piece {
    public:
        Knight(Color c) : Piece(c) {}
        bool move(int start_row, int start_col, int end_row, int end_col, const std::vector<std::vector<Piece*>>& board) override;  // Declaration of the move function
        char getName() const override;  // Declaration of getName
};



class Bishop : public Piece {
    public:
        Bishop(Color c) : Piece(c) {}
        bool move(int start_row, int start_col, int end_row, int end_col, const std::vector<std::vector<Piece*>>& board) override;  // Declaration of the move function
        char getName() const override;  // Declaration of getName
};


class Queen : public Piece {
    public:
        Queen(Color c) : Piece(c) {}
        bool move(int start_row, int start_col, int end_row, int end_col, const std::vector<std::vector<Piece*>>& board) override;  // Declaration of the move function
        char getName() const override;  // Declaration of getName
};


class King : public Piece {
    public:
        King(Color c) : Piece(c) {}
        bool move(int start_row, int start_col, int end_row, int end_col, const std::vector<std::vector<Piece*>>& board) override;  // Declaration of the move function
        char getName() const override;  // Declaration of getName
};




// Declaration of GameState class
class GameState {
    public:
        // Functions called from main cpp
        std::string current_player;
        std::vector<std::vector<Piece*>> board;
        std::vector<std::unique_ptr<Piece>> white_pieces;
        std::vector<std::unique_ptr<Piece>> black_pieces;

        // Constructor
        GameState(); 
        ~GameState(); //Destructor

        // Function to display the chess board in the console (for debugging)
        void display_board() const;
        
        // Function to handle game logic (e.g., updating turns, selecting pieces)
        void update_game_logic(std::string& piece_name, std::string& action);

        void initialize_board();
    private:
        // Functions called with in the GameState cpp
    
};


#endif  // GAMESTATE_H
