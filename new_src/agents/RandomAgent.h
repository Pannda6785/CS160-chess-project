/*
This agent chooses move randomly: for any move X, it is chosen with the probability (score(X) - min_score + 1) / sum_move{score(move) - min_score + 1}
*/

#ifndef RANDOM_AGENT_H
#define RANDOM_AGENT_H

#include "Agent.h"

class RandomAgent : public Agent {
public:
    RandomAgent(CHESS_COLOR agentColor, float moveDelay = 0.05);
    void Init() override;
    std::optional<Move> GetMove(const Board &board) override;
    
private:
    const float moveDelay; // how long should the bot wait to move (0 for instant play)
    float timeDelayed; // time passed since beginning of the move making
    
    Move _GetMove(const Board &board);
    
};

#endif //RANDOM_AGENT_H