#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(CHESS_COLOR color, Position position, bool hasMoved = false);
    
    std::unique_ptr<Piece> Clone() const override; // Deep clone
    std::vector<Move> GetPossibleMoves(const Board &board) const override;

private:
    bool IsEnPassant(const Board &board, Position enPosition) const;
    
};

#endif //PAWN_H