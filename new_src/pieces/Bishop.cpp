#include "Bishop.h"

Bishop::Bishop(CHESS_COLOR color, Position position, bool hasMoved) : Piece(BISHOP, "B", color, position, hasMoved) {}

// Deep clone
std::unique_ptr<Piece> Bishop::Clone() const {
    return std::make_unique<Bishop>(*this); 
}

std::vector<Move> Bishop::GetPossibleMoves(const Board &board) const {
    std::vector<Move> ret;

    // Check up left
    AddValidMoves(board, ret, position, {position.i - 1, position.j - 1}, -1, -1);

    // Check up right
    AddValidMoves(board, ret, position, {position.i - 1, position.j + 1}, -1, +1);

    // Check down left
    AddValidMoves(board, ret, position, {position.i + 1, position.j - 1}, +1, -1);

    // Check down right
    AddValidMoves(board, ret, position, {position.i + 1, position.j + 1}, +1, +1);

    return ret;
}

void Bishop::AddValidMoves(const Board& board, std::vector<Move>& ret, Position position, Position walk, int iIncrement, int jIncrement) const {
    while (board.IsPositionInsideBoard(walk)) {
        if (board.GetPieceByPosition(walk) == nullptr) { // Check for walk
            MOVE_TYPE type = WALK;
            ret.push_back({type, position, walk});
            walk.i += iIncrement;
            walk.j += jIncrement;
        } else if (board.GetPieceByPosition(walk) != nullptr && board.GetPieceByPosition(walk)->GetColor() != color) { // Check for attacks
            MOVE_TYPE type = ATTACK;
            ret.push_back({type, position, walk});
            break;
        } else break;
    }
}