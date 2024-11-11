#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
    King(CHESS_COLOR color, Position position, bool hasMoved = false);
    
    std::unique_ptr<Piece> Clone() const override; // Deep clone
    std::vector<Move> GetPossibleMoves(const Board &board) const override;

private:
    bool CanShortCastle(const Board &board) const;
    bool CanLongCastle(const Board &board) const;

};

#endif //KING_H
