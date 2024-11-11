#include "King.h"

King::King(CHESS_COLOR color, Position position, bool hasMoved) : Piece(KING, "K", color, position, hasMoved) {}

// Deep clone
std::unique_ptr<Piece> King::Clone() const {
    return std::make_unique<King>(*this); 
}

std::vector<Move> King::GetPossibleMoves(const Board &board) const {
    std::vector<Move> ret;
    
    // Normal moves
    std::vector<int> d = {-1, 0, 1};
    for (int di : d) {
        for (int dj : d) {
            if (di == 0 && dj == 0) continue;
            Position toPosition{position.i + di, position.j + dj};
            if (!board.IsPositionInsideBoard(toPosition)) continue;
            const Piece* attackedPiece = board.GetPieceByPosition(toPosition);
            if (attackedPiece == nullptr) { // check for walk
                ret.push_back({ WALK, position, toPosition });
            } else if (attackedPiece->GetColor() != color) { // check for attacks
                ret.push_back({ ATTACK, position, toPosition });
            } else continue;
        }
    }

    // Castling
    if (CanShortCastle(board)) {
        ret.push_back({ SHORT_CASTLING, position, Position{position.i, position.j + 2} });
    }
    if (CanLongCastle(board)) {
        ret.push_back({ LONG_CASTLING, position, Position{position.i, position.j - 2} });
    }

    return ret;
}

/*
Requirements for castling
1. The king has not previously moved.
2. The rook has not previously moved.
3. There are no pieces between the king and the rook.
4. The king may not castle out of, through, or into check.
*/

bool King::CanShortCastle(const Board &board) const {
    if (hasMoved) return false; // 1
    int i = position.i;
    const Piece* rook = board.GetPieceByPosition({i, 7});
    if (rook == nullptr || rook->HasMoved()) return false; // 2
    for (int j = 5; j <= 6; j++) {
        if (board.GetPieceByPosition({i, j}) != nullptr) return false; // 3
    }
    for (int j = 4; j <= 6; j++) {
        if (board.IsPositionAttacked(color, {i, j})) return false; // 4
    }
    return true;
}

bool King::CanLongCastle(const Board &board) const {
    if (hasMoved) return false; // 1
    int i = position.i;
    const Piece* rook = board.GetPieceByPosition({i, 0});
    if (rook == nullptr || rook->HasMoved()) return false; // 2
    for (int j = 1; j <= 3; j++) {
        if (board.GetPieceByPosition({i, j}) != nullptr) return false; // 3
    }
    for (int j = 2; j <= 4; j++) {
        if (board.IsPositionAttacked(color, {i, j})) return false; // 4
    }
    return true;
}