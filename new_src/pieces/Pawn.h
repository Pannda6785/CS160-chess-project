#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(CHESS_COLOR color, Position position) : Piece(PAWN, color, position) {}

    std::vector<Move> GetPossibleMoves(const Board &board) const override {
        std::vector<Move> ret;
        
        // Check one step walk
        Position walk = {position.i + (color == CHESS_WHITE ? -1 : +1), position.j};
        if (board.IsPositionInsideBoard(walk) && board.GetPieceByPosition(walk) == nullptr) {
            MOVE_TYPE type = WALK;
            if (color == CHESS_WHITE && walk.i == 0) type = PROMOTION;
            if (color == CHESS_BLACK && walk.i == 7) type = PROMOTION;
            ret.push_back({ type, position, walk });
        }

        // Check double walk
        Position doubleWalk = {position.i + (color == CHESS_WHITE ? -2 : +2), position.j};
        if (board.IsPositionInsideBoard(doubleWalk) && board.GetPieceByPosition(walk) == nullptr && board.GetPieceByPosition(doubleWalk)) {
            ret.push_back({ DOUBLE_WALK, position, doubleWalk });
        }

        // Check attack (including en passant)
        std::vector<Position> attacks = { Position{walk.i, walk.j - 1}, Position{walk.i, walk.j + 1} };
        for (Position attack : attacks) {
            if (!board.IsPositionInsideBoard(attack)) continue;
            if (board.GetPieceByPosition(attack) != nullptr) { // Direct attack
                MOVE_TYPE type = ATTACK;
                if (color == CHESS_WHITE && walk.i == 0) type = ATTACK_AND_PROMOTION;
                if (color == CHESS_BLACK && walk.i == 7) type = ATTACK_AND_PROMOTION;
                ret.push_back({ type, position, attack });
            }
            if (IsEnPassant(board, attack)) { // En passant 
                ret.push_back({ EN_PASSANT, position, attack });
            }
        }

        // Filter the moves that put allied King in check
        // TO DO: Filter fatal moves

        return ret;
    }

    void ExecuteMove(Move move) override {
        // TO DO: execute move
    }

private:
    bool IsEnPassant(const Board &board, Position enPosition) const {
        if (board.GetPieceByPosition(enPosition) != nullptr) return false;
        Position attackedPosition = { enPosition.i + (color == CHESS_WHITE ? +1 : -1), enPosition.j };   
        const Piece* attackedPiece = board.GetPieceByPosition(attackedPosition);
        if (attackedPiece == nullptr || attackedPiece->GetType() != PAWN) return false;
        if (board.GetLastMove() == std::nullopt) return false;
        Move move = board.GetLastMove().value();
        if (move.type != DOUBLE_WALK || move.toPosition != attackedPosition) return false;
        return true;
    }

};

#endif //PAWN_H
