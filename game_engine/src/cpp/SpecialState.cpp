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
    int kingRow = king->getRow();
    int kingCol = king->getCol();
    int pawnRowDir = (king->getColor() == Color::White) ? -1 : 1;
    Color opponentColor = (king->getColor() == Color::White) ? Color::Black : Color::White;

    //Check via possible attack directions
    //Define possible directions for rook-like (straight), bishop-like (diagonal), and knight movements
    std::vector<std::pair<int, int>> rookDirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    std::vector<std::pair<int, int>> bishopDirs = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    std::vector<std::pair<int, int>> knightMoves = {{2, 1}, {2, -1}, {-2, 1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    std::vector<std::pair<int, int >> pawnAttacks = {{pawnRowDir, -1}, {pawnRowDir, 1}};

    // Check rook and queen(rook-like) attacks
    for (const auto& dir : rookDirs) {
        int r = kingRow + dir.first;
        int c = kingCol + dir.second;
        while (r >= 0 && r < 8 && c >=0 && c < 8) {
            Piece* opponentPiece = game_state.board[r][c];
            if (opponentPiece && opponentPiece->getColor() == opponentColor) {
                if (opponentPiece->getType() == PieceType::Rook || opponentPiece->getType() == PieceType::Queen) {
                    return true; // in check via rook or queen
                }
                break; // Path blocked by another piece .. this might work this way.. revist after test
            }
            r += dir.first;
            c += dir.second;
        }
    }

    // check bishops and queen(bishop-like) attacks
    for (const auto& dir : bishopDirs) { 
        int r = kingRow + dir.first;
        int c = kingCol + dir.second;
        while (r >= 0 && r < 8 && c >=0 && c < 8) {
            Piece* opponentPiece = game_state.board[r][c];
            if (opponentPiece && opponentPiece->getColor() == opponentColor) {
                if (opponentPiece->getType() == PieceType::Bishop || opponentPiece->getType() == PieceType::Queen) {
                    return true;
                }
                break;
            }
            r += dir.first;
            c += dir.second;
        }
    }

    // Check knight attacks
    for (const auto& move : knightMoves) {
        int r = kingRow + move.first;
        int c = kingCol + move.second;
        if (r >= 0 && r < 8 && c >=0 && c < 8) {
            Piece* opponentPiece = game_state.board[r][c];
            if (opponentPiece && opponentPiece->getColor() == opponentColor && opponentPiece->getType() == PieceType::Knight) {
                return true;
            }
        }
    }

    for (const auto& dir : pawnAttacks) {
        int r = kingRow + dir.first;
        int c = kingCol + dir.second;
        if (r >= 0 &&  r < 8 && c >=0 && c < 8) {
            Piece* opponentPiece = game_state.board[r][c];
            if (opponentPiece && opponentPiece->getColor() == opponentColor && opponentPiece->getType() == PieceType::Pawn) {
                return true;
            }
        }
    }

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
