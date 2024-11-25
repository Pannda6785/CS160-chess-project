#include "RandomAgent.h"
#include "ChessbotUtilities.h"

#include <random>
#include <chrono>
#include <raylib.h>

RandomAgent::RandomAgent(CHESS_COLOR agentColor, float moveDelay) : Agent(agentColor, "Bot1"), moveDelay(moveDelay) {}

void RandomAgent::Init() {
    timeDelayed = 0;
}

std::optional<Move> RandomAgent::GetMove(const Board &board) {
    timeDelayed += GetFrameTime();
    if (timeDelayed < moveDelay) {
        return std::nullopt;
    } else {
        timeDelayed = 0;
        return _GetMove(board);
    } 
}

Move RandomAgent::_GetMove(const Board &board) {
    std::mt19937 rng(std::chrono::steady_clock().now().time_since_epoch().count());
    auto rand = [&](float r) -> float {
        return std::uniform_real_distribution<float>(0, r)(rng);
    };
    
    std::vector<std::pair<Move, float>> pool;
    float mn = 1e18;
    float mx = -1e18;
    for (const Piece* piece : board.GetPiecesByColor(agentColor)) {
        for (Move move : board.GetPossibleMoves(piece)) {
            Board newBoard = board;
            newBoard.ExecuteMove(move);
            float score = ChessbotUtilities::Evaluate(newBoard);
            mn = std::min(mn, score);
            mx = std::max(mx, score);
            pool.push_back({move, score});
        }
    }

    float sum = 0;
    for (std::pair<Move, float> &pair : pool) {
        if (agentColor == CHESS_WHITE) {
            pair.second = pair.second - mn + 1;
        } else {
            pair.second = mx - pair.second + 1; 
        }
        sum += pair.second;
    }
    float popopo = rand(sum);

    float s = 0;
    for (std::pair<Move, float> pair : pool) {
        s += pair.second;
        if (s >= popopo) return pair.first;
    }

    return pool.back().first;
}