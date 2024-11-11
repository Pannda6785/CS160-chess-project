#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
    Rook(CHESS_COLOR color, Position position, bool hasMoved = false);
    
    std::unique_ptr<Piece> Clone() const override; // Deep clone
    std::vector<Move> GetPossibleMoves(const Board &board) const override;

private:
    void AddValidMoves(const Board& board, std::vector<Move>& ret, Position position, Position walk, int iIncrement, int jIncrement) const;
    
};

#endif //ROOK_H