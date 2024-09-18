#ifndef GAMESTATE_H  // Include guard to prevent multiple inclusion
#define GAMESTATE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

class GameState;

enum class Color{
    White,
    Black
};

class Piece {
	public:
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
    	Pawn(Color color, int row, int col) {
        	this->color = color;
        	this->row = row;
        	this->col = col;
    	}

    	bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
    	std::string getName() const override;

};

class Rook : public Piece {
    public:
        Rook(Color color, int row, int col) {
                this->color = color;
                this->row = row;
                this->col = col;
        }

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;

};

class Knight : public Piece {
    public:
        Knight(Color color, int row, int col) {
                this->color = color;
                this->row = row;
                this->col = col;
        }

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;

};

class Bishop : public Piece {
    public:
        Bishop(Color color, int row, int col) {
                this->color = color;
                this->row = row;
                this->col = col;
        }

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;

};

class Queen : public Piece {
    public:
        Queen(Color color, int row, int col) {
                this->color = color;
                this->row = row;
                this->col = col;
        }

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;

};

class King : public Piece {
    public:
        King(Color color, int row, int col) {
                this->color = color;
                this->row = row;
                this->col = col;
        }

        bool isValidMove(int newRow, int newCol, GameState& game_state) const override;
        std::string getName() const override;

};

// Declaration of GameState class
class GameState {
    public:
        // Functions called from main cpp
        std::string current_player;
        std::vector<std::unique_ptr<Piece>> wp;
        std::vector<std::unique_ptr<Piece>> bp;

        // Constructor
        GameState();

        void initialize_board();
        void initialize_pieces();
        void display_board() const;
        void update_game_logic(std::string& piece_name, std::string& action);
        Piece* get_piece_at(int row, int col) const;
        void remove_piece_from_board(int row, int col, std::vector<std::unique_ptr<Piece>>& pieces);
    private:
        // Functions called with in the GameState cpp

};
#endif  // GAMESTATE_H
