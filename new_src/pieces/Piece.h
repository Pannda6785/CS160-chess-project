#ifndef PIECE_H
#define PIECE_H

class Piece;

#include <vector>
#include <memory>

#include "../ChessUnits.h"
#include "../Board.h"

// The abstract class for chess pieces 
class Piece {
public:
    Piece(PIECE_TYPE type, CHESS_COLOR color, Position position, bool hasMoved = false);

    CHESS_COLOR GetColor() const;
    PIECE_TYPE GetType() const;
    Position GetPosition() const;
    bool HasMoved() const;
    void MoveToPosition(const Position pos);
    
    virtual std::unique_ptr<Piece> Clone() const; // Deep clone
    virtual std::vector<Move> GetPossibleMoves(const Board &board) const; // Must implement

protected:
    const PIECE_TYPE type;
    const CHESS_COLOR color;
    Position position;
    bool hasMoved;

};

#endif //PIECE_H