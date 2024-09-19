#include "../header/SpecialState.h"


bool SpecialState::canCastle(GameState& game_state, const Piece* king, int newCol) {
    bool isKingside = false;
    bool isQueenside = false;

    // Determine if we are castling kingside or queenside
    if (newCol == 6 && king->getCol() == 4) {  // Kingside castling move
        isKingside = true;
    } else if (newCol == 2 && king->getCol() == 4) {  // Queenside castling move
        isQueenside = true;
    } else {
        return false;  // Not a castling move
    }

    // Determine the rook's column
    int rookCol = isKingside ? 7 : 0;  // Kingside rook is in col 7, queenside rook is in col 0
    Piece* rook = game_state.board[king->getRow()][rookCol];

    // Ensure the rook is valid and hasn't moved
    if (rook == nullptr || rook->getType() != PieceType::Rook || rook->hasMoved()) {
        return false;  // Invalid rook for castling
    }

    if (king->hasMoved()) {
        return false;
    }

    // Ensure the king is not in check or passing through check
    if (SpecialState::isInCheck(game_state, king) ||
        SpecialState::passesThroughCheck(game_state, king, (isKingside ? 5 : 3)) ||  // Check passing square
        SpecialState::passesThroughCheck(game_state, king, newCol)) {  // Check final square
        return false;
    }

    // Move the rook next to the king
    int rookNewCol = isKingside ? 5 : 3;  // Rook moves next to the king (column 5 or 3)
    game_state.board[king->getRow()][rookNewCol] = game_state.board[king->getRow()][rookCol];
    game_state.board[king->getRow()][rookCol] = nullptr;

    // Move the rook on the board and update the move log
    dynamic_cast<Rook*>(rook)->move(king->getRow(), rookNewCol);

    // Now move the king itself
    game_state.board[king->getRow()][newCol] = game_state.board[king->getRow()][king->getCol()];
    game_state.board[king->getRow()][king->getCol()] = nullptr;

    // Casted king should also update its position
    const_cast<Piece*>(king)->move(king->getRow(), newCol);  // Updating king's position

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
