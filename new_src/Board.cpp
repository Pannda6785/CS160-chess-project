#include "Board.h"

#include <iostream> // for warnings

#include "pieces/Piece.h"
#include "pieces/Pawn.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include "pieces/King.h"

Board::Board() {}
Board::Board(const Board& other) {
    for (const auto& piece : other.pieces) {
        pieces.push_back(piece->Clone());
    }
    lastMove = other.lastMove;
}
Board& Board::operator=(const Board& other) {
    if (this != &other) {
        pieces.clear();
        for (const auto& piece : other.pieces) {
            pieces.push_back(piece->Clone());
        }
        lastMove = other.lastMove;
    }
    return *this;
}

void Board::Clear() {
    pieces.clear();
    lastMove = std::nullopt;
}
void Board::Init() {
    Clear();

    // Pawns
    for (int j = 0; j < 8; j++) {
        Add(std::make_unique<Pawn>(CHESS_WHITE, Position{6, j}));
        Add(std::make_unique<Pawn>(CHESS_BLACK, Position{1, j}));
    }
    
    // Queens
    Add(std::make_unique<Queen>(CHESS_WHITE, Position{7, 3}));
    Add(std::make_unique<Queen>(CHESS_BLACK, Position{0, 3}));

    // Kings
    Add(std::make_unique<King>(CHESS_WHITE, Position{7, 4}));
    Add(std::make_unique<King>(CHESS_BLACK, Position{0, 4}));

    // Bishops
    Add(std::make_unique<Bishop>(CHESS_WHITE, Position{7, 2}));
    Add(std::make_unique<Bishop>(CHESS_WHITE, Position{7, 5}));
    Add(std::make_unique<Bishop>(CHESS_BLACK, Position{0, 2}));
    Add(std::make_unique<Bishop>(CHESS_BLACK, Position{0, 5}));

    // Knights
    Add(std::make_unique<Knight>(CHESS_WHITE, Position{7, 1}));
    Add(std::make_unique<Knight>(CHESS_WHITE, Position{7, 6}));
    Add(std::make_unique<Knight>(CHESS_BLACK, Position{0, 1}));
    Add(std::make_unique<Knight>(CHESS_BLACK, Position{0, 6}));

    // Rooks
    Add(std::make_unique<Rook>(CHESS_WHITE, Position{7, 0}));
    Add(std::make_unique<Rook>(CHESS_WHITE, Position{7, 7}));
    Add(std::make_unique<Rook>(CHESS_BLACK, Position{0, 0}));
    Add(std::make_unique<Rook>(CHESS_BLACK, Position{0, 7}));
}

bool Board::Add(std::string tag, CHESS_COLOR color, Position position, bool hasMoved = false) {
    if (tag == "K") return Add(std::make_unique<King>(color, position, hasMoved));
    if (tag == "Q") return Add(std::make_unique<Queen>(color, position, hasMoved));
    if (tag == "B") return Add(std::make_unique<Bishop>(color, position, hasMoved));
    if (tag == "N") return Add(std::make_unique<Knight>(color, position, hasMoved));
    if (tag == "R") return Add(std::make_unique<Rook>(color, position, hasMoved));
    if (tag == "P") return Add(std::make_unique<Pawn>(color, position, hasMoved));
    std::cerr << "Warning: Add failed. Tag not match to any known piece.\n";
    return false;
}
bool Board::Add(std::unique_ptr<Piece> piece) {
    for (size_t i = 0; i < pieces.size(); i++) {
        if (pieces[i]->GetPosition() == piece->GetPosition()) {
            std::cerr << "Warning: Add failed. Attempted to add on an occupied cell.\n";
            return false;
        }
    }
    pieces.push_back(std::move(piece));
    return true;
}
bool Board::Destroy(const Position position) {
    for (size_t i = 0; i < pieces.size(); i++) {
        if (pieces[i]->GetPosition() == position) {
            pieces.erase(pieces.begin() + i);
            return true;
        }
    }
    std::cerr << "Warning: Destroy failed. Attempted to destroy on an empty cell.\n";
    return false;
}
bool Board::ExecuteMove(const Move move) {
    CHESS_COLOR color = GetPieceByPosition(move.fromPosition)->GetColor(); // color of the moving piece

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

    // Move the actively moved piece (including the King in a castling)
    for (size_t i = 0; i < pieces.size(); i++) {
        if (pieces[i]->GetPosition() == move.fromPosition) {
            pieces[i]->MoveToPosition(move.toPosition);
            break;
        }
    }

    // Move the rook if castling
    if (move.type == SHORT_CASTLING || move.type == LONG_CASTLING) {
        int rank = move.fromPosition.i;
        Position rookPosition = move.type == SHORT_CASTLING ? Position{rank, 7} : Position{rank, 0};
        Position newRookPosition = move.type == SHORT_CASTLING ? Position{rank, 5} : Position{rank, 3};
        for (size_t i = 0; i < pieces.size(); i++) {
            if (pieces[i]->GetPosition() == rookPosition) {
                pieces[i]->MoveToPosition(newRookPosition);
                break;
            }
        }   
    }

    // Promotion: kill the pawn and replace it with a nicer lady
    if (move.type == PROMOTION || move.type == ATTACK_AND_PROMOTION) {
        Destroy(move.toPosition);
        if (move.promotionPiece == QUEEN) Add(std::make_unique<Queen>(color, move.toPosition));
        if (move.promotionPiece == KNIGHT) Add(std::make_unique<Knight>(color, move.toPosition));
        if (move.promotionPiece == BISHOP) Add(std::make_unique<Bishop>(color, move.toPosition));
        if (move.promotionPiece == ROOK) Add(std::make_unique<Rook>(color, move.toPosition));
    }

    SetLastMove(move);
    return true;    
}
void Board::SetLastMove(const std::optional<Move> move) {
    lastMove = move;
}

const Piece* Board::GetPieceByPosition(const Position position) const {
    for (const std::unique_ptr<Piece> &piece : pieces) {
        if (piece->GetPosition() == position) {
            return piece.get();
        }
    }
    return nullptr;
}
std::vector<const Piece*> Board::GetPiecesByColor(const CHESS_COLOR color) const {
    std::vector<const Piece*> ret;
    for (const std::unique_ptr<Piece> &piece : pieces) {
        if (piece->GetColor() == color) {
            ret.push_back(piece.get());
        }
    }
    return ret;
}
std::vector<const Piece*> Board::GetPieces() const {
    std::vector<const Piece*> ret;
    for (const std::unique_ptr<Piece> &piece : pieces) {
        ret.push_back(piece.get());
    }
    return ret;
}

std::optional<Move> Board::GetLastMove() const {
    return lastMove;
}
std::vector<Move> Board::GetPossibleMoves(const Piece* piece) const {
    std::vector<Move> moves = piece->GetPossibleMoves(*this);
    moves = FilterSelfCheckMoves(moves);
    return moves;
}

bool Board::IsPositionInsideBoard(const Position position) const {
    if (position.i < 0 || position.i >= 8) return false; 
    if (position.j < 0 || position.j >= 8) return false; 
    return true;
}
bool Board::IsMoveValid(const Move move) const {
    if (!IsPositionInsideBoard(move.fromPosition) || !IsPositionInsideBoard(move.toPosition)) return false;
    const Piece* piece = GetPieceByPosition(move.fromPosition);
    if (piece == nullptr) return false;
    for (const Move validMove : GetPossibleMoves(piece)) {
        if (move == validMove) return true;
    }
    return false;
}

bool Board::IsPositionAttacked(const CHESS_COLOR color, const Position position) const {
    for (size_t i = 0; i < pieces.size(); i++) {
        if (pieces[i]->GetColor() == color) continue;
        const Piece* piece = pieces[i].get();
        if (piece->GetType() == PAWN) { // since pawn's attack pattern is a bit weird
            int i = piece->GetPosition().i + (color == CHESS_WHITE ? +1 : -1);
            int j = piece->GetPosition().j;
            if (position == Position{i, j - 1} || position == Position{i, j + 1}) return true; 
        } else if (piece->GetType() == KING) { // since king castles
            int i = piece->GetPosition().i;
            int j = piece->GetPosition().j;
            if (std::abs(i - position.i) <= 1 && std::abs(j - position.j) <= 1) {
                return true;
            }
        } else { // Non-special pieces (Queen, Knight, Bishop, Rooks) attack the same way they move
            for (Move move : piece->GetPossibleMoves(*this)) {
                // just to clarify, by now move.type can only be either WALK or ATTACK
                if (move.toPosition == position) return true;
            }
        }
    }
    return false;
}
bool Board::IsInCheck(const CHESS_COLOR color) const {
    for (size_t i = 0; i < pieces.size(); i++) {
        if (pieces[i]->GetType() == KING && pieces[i]->GetColor() == color) {
            return IsPositionAttacked(color, pieces[i]->GetPosition());
        }
    }
    return false; // should never reach this line
}

std::vector<Move> Board::FilterSelfCheckMoves(std::vector<Move> moves) const {
    if (moves.empty()) return moves;

    CHESS_COLOR color = GetPieceByPosition(moves[0].fromPosition)->GetColor();
    std::vector<Move> ret;

    for (Move move : moves) {
        Board hypothBoard = *this;
        hypothBoard.ExecuteMove(move);
        if (!hypothBoard.IsInCheck(color)) {
            ret.push_back(move);
        }
    }
    
    return ret;
}