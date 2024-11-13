#ifndef CHESS_UNITS_H
#define CHESS_UNITS_H

// Units declaration

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
    PIECE_TYPE promotionPiece; // only and must be defined when type is PROMOTION or ATTACK_AND_PROMOTION
    bool operator==(const Move &move) const {
        if (type != move.type) return false;
        if (fromPosition != move.fromPosition) return false;
        if (toPosition != move.toPosition) return false;
        if ((type == PROMOTION || type == ATTACK_AND_PROMOTION) && promotionPiece != move.promotionPiece) return false;
        return true;
    }
};

// IO Utilities

#include <iostream>
#include <string>

// Define operators << and >> for CHESS_COLOR
inline std::ostream& operator<<(std::ostream& os, const CHESS_COLOR& color) {
    switch (color) {
        case CHESS_WHITE: os << "CHESS_WHITE"; break;
        case CHESS_BLACK: os << "CHESS_BLACK"; break;
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, CHESS_COLOR& color) {
    std::string input;
    is >> input;
    if (input == "CHESS_WHITE") color = CHESS_WHITE;
    else if (input == "CHESS_BLACK") color = CHESS_BLACK;
    return is;
}

// Define operators << and >> for CHESS_VERDICT
inline std::ostream& operator<<(std::ostream& os, const CHESS_VERDICT& verdict) {
    switch (verdict) {
        case CHESS_RUNNING: os << "CHESS_RUNNING"; break;
        case BLACK_WINS: os << "BLACK_WINS"; break;
        case WHITE_WINS: os << "WHITE_WINS"; break;
        case STALEMENT: os << "STALEMENT"; break;
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, CHESS_VERDICT& verdict) {
    std::string input;
    is >> input;
    if (input == "CHESS_RUNNING") verdict = CHESS_RUNNING;
    else if (input == "BLACK_WINS") verdict = BLACK_WINS;
    else if (input == "WHITE_WINS") verdict = WHITE_WINS;
    else if (input == "STALEMENT") verdict = STALEMENT;
    return is;
}

// Define operatos << and >> for PIECE_TYPE
inline std::ostream& operator<<(std::ostream& os, const PIECE_TYPE& piece) {
    switch (piece) {
        case PAWN: os << "PAWN"; break;
        case ROOK: os << "ROOK"; break;
        case KNIGHT: os << "KNIGHT"; break;
        case BISHOP: os << "BISHOP"; break;
        case QUEEN: os << "QUEEN"; break;
        case KING: os << "KING"; break;
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, PIECE_TYPE& piece) {
    std::string input;
    is >> input;
    if (input == "PAWN") piece = PAWN;
    else if (input == "ROOK") piece = ROOK;
    else if (input == "KNIGHT") piece = KNIGHT;
    else if (input == "BISHOP") piece = BISHOP;
    else if (input == "QUEEN") piece = QUEEN;
    else if (input == "KING") piece = KING;
    return is;
}

// Define operators << and >> for MOVE_TYPE
inline std::ostream& operator<<(std::ostream& os, const MOVE_TYPE& moveType) {
    switch (moveType) {
        case WALK: os << "WALK"; break;
        case DOUBLE_WALK: os << "DOUBLE_WALK"; break;
        case ATTACK: os << "ATTACK"; break;
        case SHORT_CASTLING: os << "SHORT_CASTLING"; break;
        case LONG_CASTLING: os << "LONG_CASTLING"; break;
        case EN_PASSANT: os << "EN_PASSANT"; break;
        case PROMOTION: os << "PROMOTION"; break;
        case ATTACK_AND_PROMOTION: os << "ATTACK_AND_PROMOTION"; break;
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, MOVE_TYPE& moveType) {
    std::string input;
    is >> input;
    if (input == "WALK") moveType = WALK;
    else if (input == "DOUBLE_WALK") moveType = DOUBLE_WALK;
    else if (input == "ATTACK") moveType = ATTACK;
    else if (input == "SHORT_CASTLING") moveType = SHORT_CASTLING;
    else if (input == "LONG_CASTLING") moveType = LONG_CASTLING;
    else if (input == "EN_PASSANT") moveType = EN_PASSANT;
    else if (input == "PROMOTION") moveType = PROMOTION;
    else if (input == "ATTACK_AND_PROMOTION") moveType = ATTACK_AND_PROMOTION;
    return is;
}

// Define operators << and >> for Position
inline std::ostream& operator<<(std::ostream& os, const Position& pos) {
    os << pos.i << ' ' << pos.j;
    // os << "(" << pos.i << ", " << pos.j << ")";
    return os;
}

inline std::istream& operator>>(std::istream& is, Position& pos) {
    is >> pos.i >> pos.j;
    // char ignore;
    // is >> ignore >> pos.i >> ignore >> ignore >> pos.j >> ignore; // Reading format: (i,j)
    return is;
}

// Define operators << and >> for Move
inline std::ostream& operator<<(std::ostream& os, const Move& move) {
    os << move.type << ' ' << move.fromPosition << ' ' << move.toPosition;
    if (move.type == PROMOTION || move.type == ATTACK_AND_PROMOTION) {
        os << ' ' << move.promotionPiece;
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, Move& move) {
    is >> move.type >> move.fromPosition >> move.toPosition;
    if (move.type == PROMOTION || move.type == ATTACK_AND_PROMOTION) {
        is >> move.promotionPiece;
    }
    return is;
}

#endif // CHESS_UNITS_H