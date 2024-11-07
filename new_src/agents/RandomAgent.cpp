#include "RandomAgent.h"

#include <random>
#include <chrono>
#include <raylib.h>

RandomAgent::RandomAgent(CHESS_COLOR agentColor, double moveDelay) : Agent(agentColor), moveDelay(moveDelay) {
    timeDelayed = 0;
}

std::optional<Move> RandomAgent::GetMove(const Board &board) {
    timeDelayed += GetFrameTime();
    if (timeDelayed < moveDelay) {
        return std::nullopt;
    } else {
        timeDelayed = 0;
        
        std::mt19937 rng(std::chrono::steady_clock().now().time_since_epoch().count());
        auto rand = [&](int n) -> int {
            return std::uniform_int_distribution<int>(0, n - 1)(rng);
        };
        
        std::vector<Move> pool;
        for (const Piece* piece : board.GetPiecesByColor(agentColor)) {
            for (Move move : board.GetPossibleMoves(piece)) {
                pool.push_back(move);
            }
        }

        if (pool.empty()) return std::nullopt; // shouldn't happen though
        return pool[rand(pool.size())];
    }        
}