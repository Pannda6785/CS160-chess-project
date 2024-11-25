#include "SearchTreeAgent.h"
#include "ChessbotUtilities.h"

#include <raylib.h>
#include <vector>
#include <iostream>

SearchTreeAgent::SearchTreeAgent(CHESS_COLOR agentColor, float moveDelay) : Agent(agentColor, "Bot2"), moveDelay(moveDelay) {}

void SearchTreeAgent::Init() {
    timeDelayed = 0;
}

std::optional<Move> SearchTreeAgent::GetMove(const Board &board) {
    timeDelayed += GetFrameTime();
    if (timeDelayed < moveDelay) {
        return std::nullopt;
    } else {
        timeDelayed = 0;
        return _GetMove(board);
    }        
}

Move SearchTreeAgent::_GetMove(const Board &board) {
    const float INF = 1e18;

    auto search = [&](auto self, const Board &board, CHESS_COLOR color, int depth) -> std::pair<float, Move> {
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
                        std::pair<float, Move> get = self(self, newBoard, color == CHESS_WHITE ? CHESS_BLACK : CHESS_WHITE, depth - 1);
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
            }
        }

        if (!hasMove) {
            if (board.IsInCheck(color)) bestScore = color == CHESS_WHITE ? -INF : +INF;
            else bestScore = 0;    
        }
        cache[ChessbotUtilities::HashBoard(board)] = bestScore;
        return std::make_pair(bestScore, bestMove);
    };
    std::pair<float, Move> get = search(search, board, agentColor, depth);

    return get.second;
}

float SearchTreeAgent::Evaluate(const Board &board) const {
    return ChessbotUtilities::Evaluate(board);
}

long long SearchTreeAgent::Hash(const Board &board) const {
    return ChessbotUtilities::HashBoard(board);
}
