#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <optional>
#include <iostream>

#include "ChessUnits.h"
#include "pieces/Piece.h"

class Board {
public:
    Board() {}
    // Deep clone
    Board(const Board& other) {
        for (const auto& piece : other.pieces) {
            pieces.push_back(piece->clone());
        }
        lastMove = other.lastMove;
    }
    Board& operator=(const Board& other) {
        if (this != &other) {
            pieces.clear();
            for (const auto& piece : other.pieces) {
                pieces.push_back(piece->clone());
            }
            lastMove = other.lastMove;
        }
        return *this;
    }

    void Clear() {
        pieces.clear();
        lastMove = std::nullopt;
    }

    bool Add(std::unique_ptr<Piece> piece) {
        for (size_t i = 0; i < pieces.size(); i++) {
            if (pieces[i]->GetPosition() == piece->GetPosition()) {
                std::cerr << "Warning: Add failed. Attempted to add on an occupied cell.\n";
                return false;
            }
        }
        pieces.push_back(std::move(piece));
        return true;
    }

    bool Destroy(const Position position) {
        for (size_t i = 0; i < pieces.size(); i++) {
            if (pieces[i]->GetPosition() == position) {
                pieces.erase(pieces.begin() + i);
                return true;
            }
        }
        std::cerr << "Warning: Destroy failed. Attempted to destroy on an empty cell.\n";
        return false;
    }

    bool ExecuteMove(const Move move) {
        // Should not happen, as the agents should only provide valid moves.
        if (!IsMoveValid(move)) {
            std::cerr << "Warning: Move is invalid.\n";
            return false;
        }

        // Kill the attacked piece
        if (move.type == ATTACK || move.type == ATTACK_AND_PROMOTION) {
            Destroy(move.toPosition);
        } else if (move.type == EN_PASSANT) {
            if (move.toPosition.i == 2) { // white did the en passant
                Destroy(Position{ 3, move.toPosition.j });
            } else { // i should be 5, black did it
                Destroy(Position{ 4, move.toPosition.j });
            }
        }

        // Move the actively moved piece
        for (size_t i = 0; i < pieces.size(); i++) {
            if (pieces[i]->GetPosition() == move.fromPosition) {
                pieces[i]->MoveToPosition(move.toPosition);
            }
        }

        // Move the rook if castling
        // TO DO: castling
        if (move.type == LONG_CASTLING) {
            
        }
        if (move.type == SHORT_CASTLING) {

        }

        // TO DO: promotion

        lastMove = move;
        return true;    
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

    std::vector<const Piece*> GetPiecesByColor(const CHESS_COLOR color) const {
        std::vector<const Piece*> ret;
        for (size_t i = 0; i < pieces.size(); i++) {
            if (pieces[i]->GetColor() == color) {
                ret.push_back(pieces[i].get());
            }
        }
        return ret;
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

    bool IsMoveValid(const Move move) {
        if (!IsPositionInsideBoard(move.fromPosition) || !IsPositionInsideBoard(move.toPosition)) return false;
        const Piece* piece = GetPieceByPosition(move.fromPosition);
        if (piece == nullptr) return false;
        for (const Move validMove : GetPossibleMoves(piece)) {
            if (move == validMove) return true;
        }
        return false;
    }

private:

    std::vector<std::unique_ptr<Piece>> pieces;
    std::optional<Move> lastMove;

};

#endif // BOARD_H