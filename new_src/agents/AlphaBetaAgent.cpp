#include "AlphaBetaAgent.h"
#include "ChessbotUtilities.h"

#include <raylib.h>
#include <vector>
#include <algorithm>

AlphaBetaAgent::AlphaBetaAgent(CHESS_COLOR agentColor, float moveDelay) : Agent(agentColor, "Bot3"), moveDelay(moveDelay) {}

void AlphaBetaAgent::Init() {
    timeDelayed = 0;
}

std::optional<Move> AlphaBetaAgent::GetMove(const Board &board) {
    timeDelayed += GetFrameTime();
    if (timeDelayed < moveDelay) {
        return std::nullopt;
    } else {
        timeDelayed = 0;
        return _GetMove(board);
    }        
}

Move AlphaBetaAgent::_GetMove(const Board &board) {
    const float INF = 1e18;
    auto search = [&](auto self, const Board &board, CHESS_COLOR color, float alpha, float beta, int depth) -> std::pair<float, Move> {
        std::vector<std::pair<Move, float>> fetch;
        for (const Piece* piece : board.GetPiecesByColor(color)) {
            for (Move move : board.GetPossibleMoves(piece)) {
                if (depth >= sortDepth) {
                    Board newBoard = board;
                    newBoard.ExecuteMove(move);
                    fetch.push_back(std::make_pair(move, ChessbotUtilities::Evaluate(newBoard)));
                } else {
                    fetch.push_back(std::make_pair(move, 0.0f));
                }
            }
        }
        if (depth >= sortDepth) {
            std::sort(fetch.begin(), fetch.end(), [&](std::pair<Move, float> x, std::pair<Move, float> y) {
                if (color == CHESS_WHITE) return x.second > y.second;
                return x.second < y.second;
            });
        }
        
        bool hasMove = false;
        float bestScore;
        Move bestMove;
        for (std::pair<Move, float> pair : fetch) {
            Move move = pair.first;
            Board newBoard = board;
            newBoard.ExecuteMove(move);
            float score;
            if (depth == 1) {
                score = ChessbotUtilities::Evaluate(newBoard);
            } else {
                std::pair<float, Move> get = self(self, newBoard, color == CHESS_WHITE ? CHESS_BLACK : CHESS_WHITE, alpha, beta, depth - 1);
                score = get.first;
            }
            if (!hasMove) {
                hasMove = true;
                bestScore = score;
                bestMove = move;
            } else if ((color == CHESS_WHITE && score > bestScore) || (color == CHESS_BLACK && score < bestScore)) {
                bestScore = score;
                bestMove = move;
            }
            if (color == CHESS_WHITE) {
                if (bestScore > beta) break;
                alpha = std::max(alpha, bestScore);
            } else {
                if (bestScore < alpha) break;
                beta = std::min(beta, bestScore);
            }
        }

        if (!hasMove) {
            if (board.IsInCheck(color)) bestScore = color == CHESS_WHITE ? -INF : +INF;
            else bestScore = 0;    
        }
        return std::make_pair(bestScore, bestMove);
    };
    std::pair<float, Move> get = search(search, board, agentColor, -INF, +INF, depth);

    return get.second;
}