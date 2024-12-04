/*
Alphabeta-pruning minimax search tree, with move ordering for first few depths.
Instead of using the native board implementation, this uses bitboard instead.
*/

#ifndef BITBOARD_AGENT_H
#define BITBOARD_AGENT_H

#include "Agent.h"

class BitboardAgent : public Agent {
public:
    BitboardAgent(CHESS_COLOR agentColor, float moveDelay = 0.05);
    void Init() override;
    std::optional<Move> GetMove(const Board &board) override;
    
private:
    const float moveDelay; // how long should the bot wait to move (0 for instant play)
    float timeDelayed; // time passed since beginning of the move making
    const int depth = 6;
    const int sortDepth = 2;

    Move _GetMove(const Board &board);

};

#endif //BITBOARD_AGENT_H