#ifndef MOVEENTRY_H
#define MOVEENTRY_H

struct MoveEntry {
    int startRow;
    int startCol;
    int endRow;
    int endCol;
    int turnNumber;
    std::string pieceName;

    MoveEntry(int startRow, int startCol, int endRow, int endCol, int turnNumber, const std::string& name)
        : startRow(startRow), startCol(startCol), endRow(endRow), endCol(endCol), turnNumber(turnNumber), pieceName(name) {}
};

#endif
