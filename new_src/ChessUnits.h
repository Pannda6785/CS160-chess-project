#ifndef CHESS_UNITS_H
#define CHESS_UNITS_H

#include "pieces/Piece.h"

enum CHESS_COLOR {
    CHESS_WHITE,
    CHESS_BLACK
};

enum CHESS_VERDICT {
    CHESS_RUNNING,
    BLACK_WINS,
    WHITE_WINS,
    STALEMENT
};

enum PIECE_TYPE {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

enum MOVE_TYPE {
    WALK,
    DOUBLE_WALK,
    ATTACK,
    SHORT_CASTLING,
    LONG_CASTLING,
    EN_PASSANT,
    PROMOTION,
    ATTACK_AND_PROMOTION,
};

struct Position {
    int i, j; // 0 <= i, j < 8. The board is white lower, black upper. Row i from upper to lower, column j from left to right.
    bool operator==(const Position &other) const {
        return i == other.i && j == other.j;
    }
    bool operator!=(const Position &other) const {
        return !((*this) == other);
    }
};

struct Move {
    MOVE_TYPE type;
    Position fromPosition;
    Position toPosition;
    PIECE_TYPE promotionPiece; // only defined when type is PROMOTION or ATTACK_AND_PROMOTION
};

#endif // CHESS_UNITS_H