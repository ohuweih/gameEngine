#include "../header/SpecialState.h"

bool SpecialState::canCastle(GameState& game_state, const Piece* king) {
    int direction = (king->getCol() == 4 && king->getColor() == Color::White) ? 1 : -1;  // Determine kingside or queenside

    // Check if the king or rook has moved, or if the king is in check
    if (SpecialState::isInCheck(game_state, king) ||
        SpecialState::passesThroughCheck(game_state, king, king->getCol() + direction)) {
        return false;
    }

    // Find the rook
    int rookCol = (direction == 1) ? 7 : 0;  // Kingside rook is at col 7, queenside rook at col 0
    Piece* rook = game_state.board[king->getRow()][rookCol];

    if (rook == nullptr || rook->getType() != PieceType::Rook || rook->hasMoved()) {
        return false;  // Invalid rook for castling
    }

    // Move the rook (cast Piece* to Rook*)
    Rook* castedRook = dynamic_cast<Rook*>(rook);
    if (castedRook) {
        int rookNewCol = (direction == 1) ? king->getCol() + 1 : king->getCol() - 1;  // Rook moves next to the king
        game_state.board[king->getRow()][rookNewCol] = game_state.board[king->getRow()][rookCol];
        game_state.board[king->getRow()][rookCol] = nullptr;
        castedRook->move(king->getRow(), rookNewCol, game_state.turnNumber);  // Call move on the casted rook
    }

    return true;  // Castling completed
}

// Function to check if the King is in check
bool SpecialState::isInCheck(const GameState& game_state, const Piece* king) {
    // Logic to check if any opponent piece can attack the King's position
    // You can iterate over the opponent's pieces and check if any can move to the King's position
    // Return true if the King is in check, otherwise false
    return false;
}

// Function to check if the King passes through check during castling
bool SpecialState::passesThroughCheck(GameState& game_state, const Piece* king, int newCol) {
    // Temporarily move the King to the new column and check if it's in check
    int originalCol = king->getCol();
    game_state.board[king->getRow()][newCol] = game_state.board[king->getRow()][originalCol];  // Temporarily move
    game_state.board[king->getRow()][originalCol] = nullptr;  // Empty the old position

    bool isCheck = SpecialState::isInCheck(game_state, king);

    // Restore the original board state
    game_state.board[king->getRow()][originalCol] = game_state.board[king->getRow()][newCol];
    game_state.board[king->getRow()][newCol] = nullptr;

    return isCheck;
}
