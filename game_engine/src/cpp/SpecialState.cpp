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
    if (SpecialState::isInCheck(game_state, king->getRow(), king->getCol(), king->getColor()) ||
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
bool SpecialState::isInCheck(const GameState& game_state, int row, int col, Color kingColor) {
    int pawnRowDir = (kingColor == Color::White) ? -1 : 1;
    Color opponentColor = (kingColor == Color::White) ? Color::Black : Color::White;

    std::cout << "Current king position: (" << row << ", " << col << ")\n";
    std::cout << "Checking for attacks from color: " << (opponentColor == Color::White ? "White" : "Black") << "\n";

    // Rook and Queen (rook-like) attacks
    std::vector<std::pair<int, int>> rookDirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (const auto& dir : rookDirs) {
        int r = row + dir.first;
        int c = col + dir.second;
        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            Piece* opponentPiece = game_state.board[r][c];
            if (opponentPiece) {
                std::cout << "Found piece at (" << r << ", " << c << "): " << opponentPiece->getName() << "\n";
                if (opponentPiece->getColor() == opponentColor && 
                    (opponentPiece->getType() == PieceType::Rook || opponentPiece->getType() == PieceType::Queen)) {
                    std::cout << "King is in check from " << opponentPiece->getName() << " at (" << r << ", " << c << ")\n";
                    return true; // In check via rook or queen
                }
                break; // Path blocked
            }
            r += dir.first;
            c += dir.second;
        }
    }

    // Bishop and Queen (bishop-like) attacks
    std::vector<std::pair<int, int>> bishopDirs = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (const auto& dir : bishopDirs) {
        int r = row + dir.first;
        int c = col + dir.second;
        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            Piece* opponentPiece = game_state.board[r][c];
            if (opponentPiece) {
                std::cout << "Found piece at (" << r << ", " << c << "): " << opponentPiece->getName() << "\n";
                if (opponentPiece->getColor() == opponentColor &&
                    (opponentPiece->getType() == PieceType::Bishop || opponentPiece->getType() == PieceType::Queen)) {
                    std::cout << "King is in check from " << opponentPiece->getName() << " at (" << r << ", " << c << ")\n";
                    return true; // In check via bishop or queen
                }
                break; // Path blocked
            }
            r += dir.first;
            c += dir.second;
        }
    }

    // Knight attacks
    std::vector<std::pair<int, int>> knightMoves = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    for (const auto& move : knightMoves) {
        int r = row + move.first;
        int c = col + move.second;
        if (r >= 0 && r < 8 && c >= 0 && c < 8) {
            Piece* opponentPiece = game_state.board[r][c];
            if (opponentPiece && opponentPiece->getColor() == opponentColor && opponentPiece->getType() == PieceType::Knight) {
                std::cout << "King is in check from Knight at (" << r << ", " << c << ")\n";
                return true; // In check via knight
            }
        }
    }

    // Pawn attacks
    std::vector<std::pair<int, int>> pawnAttacks = {{pawnRowDir, -1}, {pawnRowDir, 1}};
    for (const auto& dir : pawnAttacks) {
        int r = row + dir.first;
        int c = col + dir.second;
        if (r >= 0 && r < 8 && c >= 0 && c < 8) {
            Piece* opponentPiece = game_state.board[r][c];
            if (opponentPiece && opponentPiece->getColor() == opponentColor && opponentPiece->getType() == PieceType::Pawn) {
                std::cout << "King is in check from Pawn at (" << r << ", " << c << ")\n";
                return true; // In check via pawn
            }
        }
    }

    std::cout << "King is not in check\n";
    return false; // King is not in check
}

bool SpecialState::passesThroughCheck(GameState& game_state, const Piece* king, int newCol) {
    int originalCol = king->getCol();
    int direction = (newCol > originalCol) ? 1 : -1;

    std::cout << "Starting passesThroughCheck. King is at (" << king->getRow() << ", " << originalCol << "), newCol: " << newCol << std::endl;

    // Move through each column the king passes
    for (int col = originalCol + direction; col != newCol + direction; col += direction) {
        std::cout << "Checking if king passes through check at col = " << col << std::endl;

        // Temporarily simulate king's move to this square
        Piece* tempPiece = game_state.board[king->getRow()][col];  // Save what is currently at this square
        game_state.board[king->getRow()][col] = const_cast<Piece*>(king);  // Temporarily move the king here

        std::cout << "tempPiece location " << king->getRow() << ", " << col << std::endl;
        // Check if the king is in check at this square
        if (SpecialState::isInCheck(game_state, king->getRow(), col, king->getColor())) {
            std::cout << "King is in check at col = " << col << ", castling not allowed" << std::endl;

            // Restore the original piece
            game_state.board[king->getRow()][col] = tempPiece;  // Restore original piece
            return true;  // King passes through check, castling is not allowed
        }

        // Restore the original piece (undo the temporary move)
        game_state.board[king->getRow()][col] = tempPiece;
    }

    std::cout << "King passed through all columns safely, castling allowed" << std::endl;
    return false;  // King did not pass through check, castling is allowed
}

