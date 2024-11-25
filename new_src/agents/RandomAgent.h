#ifndef RANDOM_AGENT_H
#define RANDOM_AGENT_H

#include "Agent.h"

class RandomAgent : public Agent {
public:
    RandomAgent(CHESS_COLOR agentColor, float moveDelay = 0.4);
    void Init() override;
    std::optional<Move> GetMove(const Board &board) override;
    
private:
    const float moveDelay; // how long should the bot wait to move (0 for instant play)
    float timeDelayed; // time passed since beginning of the move making
    
};

#endif //RANDOM_AGENT_H