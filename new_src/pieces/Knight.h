#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
public:
    Knight(CHESS_COLOR color, Position position, bool hasMoved = false);
    
    std::unique_ptr<Piece> Clone() const override; // Deep clone
    std::vector<Move> GetPossibleMoves(const Board &board) const override;

private:
    
};

#endif //KNIGHT_H