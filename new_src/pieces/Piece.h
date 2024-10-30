#ifndef PIECE_H
#define PIECE_H

class Piece; // Forward declaration (circular dependency).

#include <vector>

#include "../ChessUnits.h"
#include "../Board.h"

class Piece {
public:
    Piece(PIECE_TYPE type, CHESS_COLOR color, Position position) : type(type), color(color), position(position), hasMoved(false) {}
    CHESS_COLOR GetColor() const {
        return color;
    }
    PIECE_TYPE GetType() const {
        return type;
    }
    Position GetPosition() const {
        return position;
    }
    bool HasMoved() const {
        return hasMoved;
    }
    
    virtual std::vector<Move> GetPossibleMoves(const Board &board) const;
    virtual void ExecuteMove(Move move);

protected:
    const PIECE_TYPE type;
    const CHESS_COLOR color;
    Position position;
    bool hasMoved;

};

#endif //PIECE_H
