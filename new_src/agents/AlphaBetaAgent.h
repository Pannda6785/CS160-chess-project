/*
Alphabeta-pruning minimax search tree, with move ordering for first few depths.
*/

#ifndef ALPHA_BETA_AGENT_H
#define ALPHA_BETA_AGENT_H

#include "Agent.h"

class AlphaBetaAgent : public Agent {
public:
    AlphaBetaAgent(CHESS_COLOR agentColor, float moveDelay = 0.12);
    void Init() override;
    std::optional<Move> GetMove(const Board &board) override;
    
private:
    const float moveDelay; // how long should the bot wait to move (0 for instant play)
    float timeDelayed; // time passed since beginning of the move making
    const int depth = 4;
    const int sortDepth = 2;

    Move _GetMove(const Board &board);

};

#endif //ALPHA_BETA_AGENT_H