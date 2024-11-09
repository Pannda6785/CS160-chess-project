#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
public:
    Queen(CHESS_COLOR color, Position position, bool hasMoved = false);
    
    std::unique_ptr<Piece> Clone() const override; // Deep clone
    std::vector<Move> GetPossibleMoves(const Board &board) const override;

private:
    void AddValidMoves(const Board& board, std::vector<Move>& ret, Position position, Position walk, int iIncrement, int jIncrement) const;
};

#endif //QUEEN_H