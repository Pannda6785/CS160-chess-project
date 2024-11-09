#include "Rook.h"

Rook::Rook(CHESS_COLOR color, Position position, bool hasMoved) : Piece(ROOK, "R", color, position, hasMoved) {}

// Deep clone
std::unique_ptr<Piece> Rook::Clone() const {
    return std::make_unique<Rook>(*this); 
}

std::vector<Move> Rook::GetPossibleMoves(const Board &board) const {
    std::vector<Move> ret;

    // Check left
    AddValidMoves(board, ret, position, {position.i, position.j - 1}, 0, -1);

    // Check right
    AddValidMoves(board, ret, position, {position.i, position.j + 1}, 0, +1);

    // Check up
    AddValidMoves(board, ret, position, {position.i - 1, position.j}, -1, 0);

    // Check down
    AddValidMoves(board, ret, position, {position.i + 1, position.j}, +1, 0);
    
    // Filter the moves that put allied King in check
    ret = board.FilterSelfCheckMoves(ret);

    return ret;
}

void Rook::AddValidMoves(const Board& board, std::vector<Move>& ret, Position position, Position walk, int iIncrement, int jIncrement) const {
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