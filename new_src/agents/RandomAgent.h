#ifndef RANDOM_AGENT_H
#define RANDOM_AGENT_H

#include <random>
#include <chrono>

#include "raylib.h"
#include "Agent.h"

class RandomAgent : public Agent {
public:
    RandomAgent(CHESS_COLOR agentColor, double moveDelay = 0.6) : Agent(agentColor), moveDelay(moveDelay) {
        timeDelayed = 0;
    }

    std::optional<Move> GetMove(const Board &board) override {
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

            if (pool.empty()) return std::nullopt;
            return pool[rand(pool.size())];
        }        
    }  
private:
    const double moveDelay; // how long should the bot wait to move (0 for instant play)
    double timeDelayed;
    
};


#endif //RANDOM_AGENT_H