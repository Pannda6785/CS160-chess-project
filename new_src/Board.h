#ifndef BOARD_H
#define BOARD_H

class Board;

#include <vector>
#include <memory>
#include <optional>

#include "ChessUnits.h"
#include "pieces/Piece.h"

class Board {
public:
    Board();
    // Deep clone
    Board(const Board& other);
    Board& operator=(const Board& other);

    void Clear(); // wipe all pieces out of the board
    void Init(); // make the board the default configuration (2 kings, 2 queens, 16 pawns,... that kind of meaning)

    bool Add(std::unique_ptr<Piece> piece);
    bool Destroy(const Position position);
    bool ExecuteMove(const Move move); // Should only provide valid move

    std::optional<Move> GetLastMove() const;
    const Piece* GetPieceByPosition(const Position position) const;
    std::vector<const Piece*> GetPiecesByColor(const CHESS_COLOR color) const;
    std::vector<Move> GetPossibleMoves(const Piece* piece) const;

    bool IsPositionInsideBoard(const Position position) const;
    bool IsMoveValid(const Move move) const;
    
    bool IsPositionAttacked(const CHESS_COLOR color, const Position position) const; // Is the position attacked by the other color?
    bool IsInCheck(const CHESS_COLOR color) const; // Is color's king attacked?

    std::vector<Move> FilterSelfCheckMoves(std::vector<Move> moves) const; // filter the moves that doesn't help allied king out of check, or put allied king in check

private:
    std::vector<std::unique_ptr<Piece>> pieces;
    std::optional<Move> lastMove;

};

#endif // BOARD_H
