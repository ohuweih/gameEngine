#ifndef GAMESTATE_H  // Include guard to prevent multiple inclusion
#define GAMESTATE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class GameState;

enum class Color{
    White,
    Black
};


class Piece {
	public:
        Piece(Color color, int row, int col)
            : color(color), row(row), col(col) {}

        virtual ~Piece() = default;  // Default virtual destructor for polymorphism what ever that is

    	virtual bool isValidMove(int newRow, int newCol, GameState& game_state) const = 0;
    	virtual void move(int newRow, int newCol) {
        	row = newRow;
        	col = newCol;
    	}

    	int getRow() const { return row; }
    	int getCol() const { return col; }
        Color getColor() const { return color; }
    	virtual std::string getName() const = 0;


	protected:
    	int row;
    	int col;
    	Color color;
};


class Pawn : public Piece {
    public:
    	Pawn(Color color, int row, int col)
            : Piece(color, row, col) {}

    	bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
    	std::string getName() const override;

};

class Rook : public Piece {
    public:
        Rook(Color color, int row, int col) 
         : Piece(color, row, col) {} 

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;

};

class Knight : public Piece {
    public:
        Knight(Color color, int row, int col) 
            : Piece(color, row, col) {}

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;

};

class Bishop : public Piece {
    public:
        Bishop(Color color, int row, int col)
            : Piece(color, row, col) {}

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;

};

class Queen : public Piece {
    public:
        Queen(Color color, int row, int col)
             : Piece(color, row, col) {}

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;

};

class King : public Piece {
    public:
        King(Color color, int row, int col)
             : Piece(color, row, col) {}

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;

};


// Declaration of GameState class
class GameState {
    public:
        // Functions called from main cpp
        std::string currentPlayer;
        std::vector<std::vector<Piece*>> board;

        // Constructor
        GameState(); 
//        ~GameState(); //Destructor

        void initialize_board();
        void display_board() const;
        bool move_piece(int startRow, int startCol, int endRow, int endCol);
//        void update_game_logic(std::string& piece_name, std::string& action);

    private:
        // Functions called with in the GameState cpp
        std::vector<std::unique_ptr<Piece>> pieces;
        void place_major_pieces(int row, Color color);
};


#endif  // GAMESTATE_H
