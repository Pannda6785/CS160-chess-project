#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(CHESS_COLOR color, Position position);
    
    std::unique_ptr<Piece> Clone() const override; // Deep clone
    std::vector<Move> GetPossibleMoves(const Board &board) const override;

private:
    void AddValidMoves(const Board& board, std::vector<Move>& ret, Position position, Position walk, int iIncrement, int jIncrement) const;
};

#endif //BISHOP_H