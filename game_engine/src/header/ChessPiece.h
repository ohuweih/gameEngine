// ChessPiece.h
#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>

class GameState;

class ChessPiece {
public:
    std::string name;
    std::string color;
    
    ChessPiece(const std::string& name, const std::string& color)
        : name(name), color(color) {}

    std::string get_color() const {
        return color;
    }

    virtual bool is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) = 0;
};

#endif

