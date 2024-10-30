#ifndef BOARD_H
#define BOARD_H

class Board;

#include <vector>
#include <memory>
#include <optional>

#include "ChessUnits.h"
#include "pieces/Piece.h"
#include "pieces/Pawn.h"
// #include "pieces/Rook.h"
// #include "pieces/Knight.h"
// #include "pieces/Bishop.h"
// #include "pieces/Queen.h"
// #include "pieces/King.h"

class Board {
public:

    // Makes the board the default board
    void Init() {
        // TO DO: add properly
        Add(std::make_unique<Pawn>(CHESS_WHITE, Position{6, 4}));
    }

    bool Add(std::unique_ptr<Piece> piece) {
        for (size_t i = 0; i < pieces.size(); i++) {
            if (pieces[i]->GetPosition() == piece->GetPosition()) return false;
        }
        pieces.push_back(std::move(piece));
        return true;
    }

    bool Destroy(Position position) {
        for (size_t i = 0; i < pieces.size(); i++) {
            if (pieces[i]->GetPosition() == position) {
                pieces.erase(pieces.begin() + i);
                return true;
            }
        }
        return false;
    }

    std::optional<Move> GetLastMove() const {
        return lastMove;
    }
    
    const Piece* GetPieceByPosition(const Position position) const {
        for (size_t i = 0; i < pieces.size(); i++) {
            if (pieces[i]->GetPosition() == position) {
                return pieces[i].get();
            }
        }
        return nullptr;
    }

    std::vector<Move> GetPossibleMoves(const Piece* piece) const {
        return piece->GetPossibleMoves(*this);
    }

    bool IsPositionInsideBoard(const Position position) const {
        if (position.i < 0 || position.i >= 8) return false; 
        if (position.j < 0 || position.j >= 8) return false; 
        return true;
    }

    // Is the position attacked by the otherColor(color)?
    bool IsPositionAttacked(const CHESS_COLOR color) const {
        // TO DO: is position attacked
    }

    // Is color's king attacked?
    bool IsInCheck(const CHESS_COLOR color) const {
        // TO DO: is in check
    }

private:

    std::vector<std::unique_ptr<Piece>> pieces;
    std::optional<Move> lastMove;

};

#endif // BOARD_H
