#ifndef PIECE_H
#define PIECE_H

class Piece;

#include <vector>
#include <memory>
#include <string>

#include "../ChessUnits.h"
#include "../Board.h"

// The abstract class for chess pieces 
class Piece {
public:
    Piece(PIECE_TYPE type, std::string tag, CHESS_COLOR color, Position position, bool hasMoved = false);

    CHESS_COLOR GetColor() const;
    PIECE_TYPE GetType() const;
    Position GetPosition() const;
    std::string GetTag() const; // {K, Q, N, B, R, P}

    bool HasMoved() const;
    void MoveToPosition(const Position pos);
    
    virtual std::unique_ptr<Piece> Clone() const; // Deep clone
    virtual std::vector<Move> GetPossibleMoves(const Board &board) const; // Must implement. Returns the moves without regard to the king's safety (i.e. it may put king in check). It is necessary, think of the piece as a freeman.

protected:
    const PIECE_TYPE type;
    const CHESS_COLOR color;
    Position position;
    bool hasMoved;

private:
    std::string tag;

};

#endif //PIECE_H
