#ifndef ALPHA_BETA_AGENT_H
#define ALPHA_BETA_AGENT_H

#include "Agent.h"
#include <map>

class AlphaBetaAgent : public Agent {
public:
    AlphaBetaAgent(CHESS_COLOR agentColor, float moveDelay = 0.2);
    void Init() override;
    std::optional<Move> GetMove(const Board &board) override;
    
private:
    const float moveDelay; // how long should the bot wait to move (0 for instant play)
    float timeDelayed; // time passed since beginning of the move making
    const int depth = 4;
    std::map<long long, float> cache;

    Move _GetMove(const Board &board);
    float Evaluate(const Board &board) const;
    long long Hash(const Board &board) const;

};

#endif //ALPHA_BETA_AGENT_H