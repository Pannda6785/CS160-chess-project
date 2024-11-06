#ifndef PIECE_H
#define PIECE_H

class Board;

#include <vector>

#include "../ChessUnits.h"
#include "../Board.h"

// The abstract class for chess pieces 
class Piece {
public:
    Piece(PIECE_TYPE type, CHESS_COLOR color, Position position, bool hasMoved = false) : type(type), color(color), position(position), hasMoved(hasMoved) {}
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
    void MoveToPosition(const Position pos) {
        position = pos;
        hasMoved = true;
    }
    
    virtual std::unique_ptr<Piece> clone() const; // Deep clone
    virtual std::vector<Move> GetPossibleMoves(const Board &board) const;

protected:
    const PIECE_TYPE type;
    const CHESS_COLOR color;
    Position position;
    bool hasMoved;

};

#endif //PIECE_H
