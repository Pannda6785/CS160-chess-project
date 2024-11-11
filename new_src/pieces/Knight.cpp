#include "Knight.h"

Knight::Knight(CHESS_COLOR color, Position position, bool hasMoved) : Piece(KNIGHT, "N", color, position, hasMoved) {}

// Deep clone
std::unique_ptr<Piece> Knight::Clone() const {
    return std::make_unique<Knight>(*this); 
}

std::vector<Move> Knight::GetPossibleMoves(const Board &board) const {
    std::vector<Move> ret;
    
    std::vector<int> d = {-2, -1, 1, 2};
    for (int di : d) {
        for (int dj : d) {
            if (di * di == dj * dj) continue; // compare the absolute values
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

    return ret;
}