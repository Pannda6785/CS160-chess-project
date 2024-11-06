#ifndef AGENT_H
#define AGENT_H

class Board;

#include "../ChessUnits.h"
#include "../Board.h"

// The abstract class for chess agent
class Agent {
public:
    Agent(CHESS_COLOR agentColor) : agentColor(agentColor) {}
    CHESS_COLOR GetColor() const {
        return agentColor;
    }

    virtual std::optional<Move> GetMove(const Board &board);
    virtual std::optional<Position> GetSelectedPosition() const { return std::nullopt; }

protected:
    const CHESS_COLOR agentColor;
    
};

#endif //AGENT_H
