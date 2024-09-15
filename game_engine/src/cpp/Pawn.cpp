#include "../header/GameState.h"
#include "../header/Pawn.h"
#include <iostream>


// Function for valid or invalid move. This should be broke later in the game for the crazy part of the game
bool Pawn::is_valid_move(GameState& game_state, int start_row, int start_col, int end_row, int end_col) {
    int direction = (color == "white") ? -1 : 1; // This should make white move up and black move down... Hopefuly lol

    // Ensure the we are with in the bounds of the game_state.board
    if (end_row < 0 || end_row > 7 || end_col < 0 || end_col > 7){
        return false;
    }


    //Pawn move
    if (start_col == end_col && game_state.board[end_row][end_col]->name == "") {
        if (end_row == start_row + direction) {
            return true; // Move forward
        }


        if ((color == "white" && start_row == 6 && end_row == 4 && game_state.board[5][end_col]->name == "" ) ||
            (color == "black" && start_row == 1 && end_row == 3 && game_state.board[2][end_col]->name =="" )) {
            return true; // Pawn two space start move if both spaces are clear.
        }
    }


    // Pawn Capture
    if (std::abs(start_col - end_col) == 1 && end_row == start_row + direction) {
        if (game_state.board[end_row][end_col]->name != "" && game_state.board[end_row][end_col]->color != color) {
            return true;
        }
    }

    return false;
}

