#include "Piece.h"

Piece::Piece(PIECE_TYPE type, CHESS_COLOR color, Position position, bool hasMoved) : type(type), color(color), position(position), hasMoved(hasMoved) {}

CHESS_COLOR Piece::GetColor() const {
    return color;
}
PIECE_TYPE Piece::GetType() const {
    return type;
}
Position Piece::GetPosition() const {
    return position;
}
bool Piece::HasMoved() const {
    return hasMoved;
}
void Piece::MoveToPosition(const Position pos) {
    position = pos;
    hasMoved = true;
}

std::unique_ptr<Piece> Piece::Clone() const { 
    // Is not expected to be called
    return nullptr;
}
std::vector<Move> Piece::GetPossibleMoves(const Board &board) const {
    // Is not expected to be called
    return {};
}
