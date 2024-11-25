#include "ChessbotUtilities.h"
#include "BitboardAgent.h"
#define VIRGO_IMPLEMENTATION
#include "virgo.h"

#include <raylib.h>
#include <vector>
#include <algorithm>

namespace VirgoAdaptUtilities {
    virgo::Chessboard BoardToBitboard(const Board &board, CHESS_COLOR color);
    Move VirgoMoveToMove(const Board& board, uint16_t move);
}
namespace BitboardEvaluateUtilities {
    inline float Evaluate(const virgo::Chessboard &bitboard);
}

BitboardAgent::BitboardAgent(CHESS_COLOR agentColor, float moveDelay) : Agent(agentColor, "Bot3"), moveDelay(moveDelay) {}

void BitboardAgent::Init() {
    timeDelayed = 0;
    virgo::virgo_init();
}

std::optional<Move> BitboardAgent::GetMove(const Board &board) {
    timeDelayed += GetFrameTime();
    if (timeDelayed < moveDelay) {
        return std::nullopt;
    } else {
        timeDelayed = 0;
        return _GetMove(board);
    }        
}

Move BitboardAgent::_GetMove(const Board &board) {
    virgo::Chessboard bitboard = VirgoAdaptUtilities::BoardToBitboard(board, agentColor);
    CHESS_COLOR color = agentColor;

    const float INF = 1e18;
    int cnt = 0;
    std::vector<uint16_t> stk;
    auto search = [&](auto& self, float alpha, float beta, int depth) -> std::pair<float, uint16_t> {
        cnt++;  // Counting nodes explored
    
        std::vector<uint16_t> moves; 
        if (color == CHESS_WHITE) virgo::get_legal_moves<virgo::VIRGOWHITE>(bitboard, moves);
        if (color == CHESS_BLACK) virgo::get_legal_moves<virgo::VIRGOBLACK>(bitboard, moves);

        if (depth >= sortDepth) {
            std::vector<float> scores;
            std::vector<int> order;
            for (uint16_t move : moves) {
                // perform the move
                if (color == CHESS_WHITE) {
                    color = CHESS_BLACK;
                    virgo::make_move<virgo::VIRGOWHITE>(move, bitboard);
                } else {
                    color = CHESS_WHITE;                
                    virgo::make_move<virgo::VIRGOBLACK>(move, bitboard);
                }
                // fetch the score
                scores.push_back(BitboardEvaluateUtilities::Evaluate(bitboard));
                // undo the move
                if (color == CHESS_BLACK) {
                    color = CHESS_WHITE;
                    virgo::take_move<virgo::VIRGOWHITE>(bitboard);
                } else {
                    color = CHESS_BLACK;
                    virgo::take_move<virgo::VIRGOBLACK>(bitboard);
                }
                order.push_back(order.size());
            }
            if (color == CHESS_WHITE) {
                std::sort(order.begin(), order.end(), std::greater<float>());
            } else {
                std::sort(order.begin(), order.end());
            }
            std::vector<uint16_t> newMoves;
            for (int i : order) {
                newMoves.push_back(moves[i]);
            }
            moves = newMoves;
        }

        bool hasMove = false;
        uint16_t bestMove;
        float bestScore;

        for (uint16_t move : moves) {
            // perform the move
            if (color == CHESS_WHITE) {
                color = CHESS_BLACK;
                virgo::make_move<virgo::VIRGOWHITE>(move, bitboard);
            } else {
                color = CHESS_WHITE;                
                virgo::make_move<virgo::VIRGOBLACK>(move, bitboard);
            }
            stk.push_back(move);

            // evaluate
            float score;
            if (depth == 1) {
                score = BitboardEvaluateUtilities::Evaluate(bitboard);
            } else {
                std::pair<float, uint16_t> get = self(self, alpha, beta, depth - 1);
                score = get.first;
            }

            // undo the move
            if (color == CHESS_BLACK) {
                color = CHESS_WHITE;
                virgo::take_move<virgo::VIRGOWHITE>(bitboard);
            } else {
                color = CHESS_BLACK;
                virgo::take_move<virgo::VIRGOBLACK>(bitboard);
            }
            stk.pop_back();

            // update
            if (!hasMove) {
                hasMove = true;
                bestScore = score;
                bestMove = move;
            } else if ((color == CHESS_WHITE && score > bestScore) || (color == CHESS_BLACK && score < bestScore)) {
                bestScore = score;
                bestMove = move;
            }

            // alpha-beta cuts
            if (color == CHESS_WHITE) {
                if (bestScore > beta) break;
                alpha = std::max(alpha, bestScore);
            } else {
                if (bestScore < alpha) break;
                beta = std::min(beta, bestScore);
            }
        }

        if (!hasMove) {
            bool isInCheck;
            if (color == CHESS_WHITE) isInCheck = virgo::is_in_check<virgo::VIRGOWHITE>(bitboard);
            else isInCheck = virgo::is_in_check<virgo::VIRGOBLACK>(bitboard);
            if (isInCheck) bestScore = color == CHESS_WHITE ? -INF : +INF;
            else bestScore = 0;    
        }

        return std::make_pair(bestScore, bestMove);
    };
    std::pair<float, uint16_t> get = search(search, -INF, +INF, depth);
    return VirgoAdaptUtilities::VirgoMoveToMove(board, get.second);
}

namespace VirgoAdaptUtilities {
    virgo::Chessboard BoardToBitboard(const Board &board, CHESS_COLOR color) {
        std::string fen = ChessbotUtilities::GetFEN(board, color);
        return virgo::position_from_fen(fen);
    }

    Move VirgoMoveToMove(const Board& board, uint16_t move) {
        std::string str = virgo::string::move_to_string(move);
        Position fromPosition{ 8 - (str[1] - '0'), str[0] - 'a' };
        Position toPosition{ 8 - (str[3] - '0'), str[2] - 'a' };
        PIECE_TYPE promotionPiece;
        if (str.size() == 5) {
            char ch = str[4];
            if (ch == 'r') promotionPiece = ::ROOK;
            if (ch == 'b') promotionPiece = ::BISHOP;
            if (ch == 'n') promotionPiece = ::KNIGHT;
            if (ch == 'q') promotionPiece = ::QUEEN;
        }
        for (Move move : board.GetPossibleMoves(board.GetPieceByPosition(fromPosition))) {
            if (move.toPosition == toPosition) {
                if (move.type == PROMOTION || move.type == ATTACK_AND_PROMOTION) {
                    move.promotionPiece = promotionPiece;
                    return move;
                } else {
                    return move;
                }
            }
        }
        return Move(); // should not reach here
    }

}


namespace BitboardEvaluateUtilities {
    const int pawnValue = 100;
    const int knightValue = 300;
    const int bishopValue = 320;
    const int rookValue = 500;
    const int queenValue = 900;
    const float endgameMaterialStart = rookValue * 2 + bishopValue + knightValue;
    
    const int pawnPositionalValue[64] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        50, 50, 50, 50, 50, 50, 50, 50,
        10, 10, 20, 30, 30, 20, 10, 10,
        5,  5, 10, 25, 25, 10,  5,  5,
        0,  0,  0, 20, 20,  0,  0,  0,
        5, -5,-10,  0,  0,-10, -5,  5,
        5, 10, 10,-20,-20, 10, 10,  5,
        0,  0,  0,  0,  0,  0,  0,  0
    };
    const int knightPositionalValue[64] = {
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50
    };
    const int bishopPositionalValue[64] = {
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5, 10, 10,  5,  0,-10,
        -10,  5,  5, 10, 10,  5,  5,-10,
        -10,  0, 10, 10, 10, 10,  0,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10,  5,  0,  0,  0,  0,  5,-10,
        -20,-10,-10,-10,-10,-10,-10,-20
    };
    const int rookPositionalValue[64] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        5, 10, 10, 10, 10, 10, 10,  5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        0,  0,  0,  5,  5,  0,  0,  0
    };
    const int queenPositionalValue[64] = {
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5,  5,  5,  5,  0,-10,
        -5,  0,  5,  5,  5,  5,  0, -5,
        0,  0,  5,  5,  5,  5,  0, -5,
        -10,  5,  5,  5,  5,  5,  0,-10,
        -10,  0,  5,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
    };
    const int kingEarlyPositionalValue[64] = {
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -10,-20,-20,-20,-20,-20,-20,-10,
        20, 20,  0,  0,  0,  0, 20, 20,
        20, 30, 10,  0,  0, 10, 30, 20
    };
    const int kingEndPositionalValue[64] = {
        -50,-40,-30,-20,-20,-30,-40,-50,
        -30,-20,-10,  0,  0,-10,-20,-30,
        -30,-10, 20, 30, 30, 20,-10,-30,
        -30,-10, 30, 40, 40, 30,-10,-30,
        -30,-10, 30, 40, 40, 30,-10,-30,
        -30,-10, 20, 30, 30, 20,-10,-30,
        -30,-30,  0,  0,  0,  0,-30,-30,
        -50,-30,-30,-30,-30,-30,-30,-50
    };

    inline float Evaluate(const virgo::Chessboard &bitboard) {
        int materialScore = 0;
        int positionalScoreWithoutKings = 0;

        int whiteKingPositionalEarly;
        int whiteKingPositionalEnd;
        int blackKingPositionalEarly;
        int blackKingPositionalEnd;

        int whiteMaterialScoreWithoutPawns = 0;
        int blackMaterialScoreWithoutPawns = 0;

        for (int square = 0; square < 64; square++) {
            virgo::Piece piece = bitboard[square].first;
            virgo::Player color = bitboard[square].second;
            if (piece == virgo::EMPTY) continue;
            bool isWhite = color == virgo::VIRGOWHITE;
            int sgn = isWhite ? +1 : -1;
            int i = square / 8;
            int j = square % 8;
            if (!isWhite) i = 7 - i;
            int cell = 8 * i + j;

            switch (piece) {
                case virgo::KING: 
                    if (isWhite) {
                        whiteKingPositionalEarly = kingEarlyPositionalValue[cell];
                        whiteKingPositionalEnd = kingEarlyPositionalValue[cell];
                    } else {
                        blackKingPositionalEarly = kingEarlyPositionalValue[cell];
                        blackKingPositionalEnd = kingEarlyPositionalValue[cell];
                    }
                    break;
                case virgo::QUEEN:
                    materialScore += sgn * queenValue;
                    positionalScoreWithoutKings += sgn * queenPositionalValue[cell];

                    if (isWhite) whiteMaterialScoreWithoutPawns += queenValue;
                    else blackMaterialScoreWithoutPawns += queenValue;
                    break;
                case virgo::ROOK: 
                    materialScore += sgn * rookValue;
                    positionalScoreWithoutKings += sgn * rookPositionalValue[cell];

                    if (isWhite) whiteMaterialScoreWithoutPawns += rookValue;
                    else blackMaterialScoreWithoutPawns += rookValue;
                    break;
                case virgo::BISHOP:
                    materialScore += sgn * bishopValue;
                    positionalScoreWithoutKings += sgn * bishopPositionalValue[cell];

                    if (isWhite) whiteMaterialScoreWithoutPawns += bishopValue;
                    else blackMaterialScoreWithoutPawns += bishopValue;
                    break;
                case virgo::KNIGHT:
                    materialScore += sgn * knightValue;
                    positionalScoreWithoutKings += sgn * knightPositionalValue[cell];

                    if (isWhite) whiteMaterialScoreWithoutPawns += knightValue;
                    else blackMaterialScoreWithoutPawns += knightValue;
                    break;
                case virgo::PAWN: 
                    materialScore += sgn * pawnValue;
                    positionalScoreWithoutKings += sgn * pawnPositionalValue[cell];

                    break;
            }
        }

        float whiteEndgameWeight = 1.0f - std::min(1.0f, (float)whiteMaterialScoreWithoutPawns / endgameMaterialStart);
        float blackEndgameWeight = 1.0f - std::min(1.0f, (float)blackMaterialScoreWithoutPawns / endgameMaterialStart);

        float positionalScore = positionalScoreWithoutKings;
        positionalScore += whiteKingPositionalEarly * (1 - whiteEndgameWeight) + whiteKingPositionalEnd * whiteEndgameWeight;
        positionalScore -= blackKingPositionalEarly * (1 - blackEndgameWeight) + blackKingPositionalEnd * blackEndgameWeight;

        return materialScore + positionalScore;
    }
}