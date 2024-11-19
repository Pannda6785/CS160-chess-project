#include "AlphaBetaAgent.h"
#include "ChessbotUtilities.h"

#include <raylib.h>
#include <vector>
#include <iostream>

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
    int cnt = 0;
    auto search = [&](auto self, const Board &board, CHESS_COLOR color, float alpha, float beta, int depth) -> std::pair<float, Move> {
        cnt++;
        bool hasMove = false;
        float bestScore;
        Move bestMove;
        for (const Piece* piece : board.GetPiecesByColor(color)) {
            for (Move move : board.GetPossibleMoves(piece)) {
                Board newBoard = board;
                newBoard.ExecuteMove(move);
                float score;
                long long h = ChessbotUtilities::HashBoard(newBoard);
                if (cache.count(h)) {
                    score = cache[h];
                } else {
                    if (depth == 1) {
                        score = Evaluate(newBoard);
                    } else {
                        std::pair<float, Move> get = self(self, newBoard, color == CHESS_WHITE ? CHESS_BLACK : CHESS_WHITE, alpha, beta, depth - 1);
                        score = get.first;
                    }
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
        }

        if (!hasMove) {
            if (board.IsInCheck(color)) bestScore = color == CHESS_WHITE ? -INF : +INF;
            else bestScore = 0;    
        }
        cache[ChessbotUtilities::HashBoard(board)] = bestScore;
        return std::make_pair(bestScore, bestMove);
    };
    std::pair<float, Move> get = search(search, board, agentColor, -INF, +INF, depth);
    std::cout << "Node explored " << cnt << '\n';
    std::cout << get.first << " ||| " << get.second << '\n';

    return get.second;
}

float AlphaBetaAgent::Evaluate(const Board &board) const {
    return ChessbotUtilities::Evaluate(board);
}

long long AlphaBetaAgent::Hash(const Board &board) const {
    return ChessbotUtilities::HashBoard(board);
}
