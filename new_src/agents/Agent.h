#ifndef AGENT_H
#define AGENT_H

#include "../ChessUnits.h"
#include "../Board.h"

// The abstract class for a chess agent
class Agent {
public:
    Agent(CHESS_COLOR agentColor);
    CHESS_COLOR GetColor() const;

    // Fetching information on the decisions of the agent during the making of a move.
    virtual std::optional<Position> GetSelectedPosition() const;
    virtual bool IsPromoting() const; 
    virtual int GetPromotingFile() const;

    // Must be implemented by any agent
    virtual std::optional<Move> GetMove(const Board &board);

protected:
    const CHESS_COLOR agentColor;
    
};

#endif //AGENT_H
