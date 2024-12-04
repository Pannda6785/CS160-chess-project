/*
Standard minimax search tree.
*/

#ifndef SEARCH_TREE_AGENT_H
#define SEARCH_TREE_AGENT_H

#include "Agent.h"

class SearchTreeAgent : public Agent {
public:
    SearchTreeAgent(CHESS_COLOR agentColor, float moveDelay = 0.05);
    void Init() override;
    std::optional<Move> GetMove(const Board &board) override;
    
private:
    const float moveDelay; // how long should the bot wait to move (0 for instant play)
    float timeDelayed; // time passed since beginning of the move making
    const int depth = 3;

    Move _GetMove(const Board &board);

};

#endif //SEARCH_TREE_AGENT_H