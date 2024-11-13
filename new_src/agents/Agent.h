#ifndef AGENT_H
#define AGENT_H

#include <string>

#include "../ChessUnits.h"
#include "../Board.h"

// The abstract class for a chess agent
class Agent {
public:
    Agent(CHESS_COLOR agentColor, std::string tag);
    CHESS_COLOR GetColor() const;
    std::string GetTag() const;

    virtual void Init(); // Game undergone something that agent should not retain memory

    // Fetching information on the decisions of the agent during the making of a move.
    virtual std::optional<Position> GetSelectedPosition() const;
    virtual bool IsPromoting() const; 
    virtual int GetPromotingFile() const;
    virtual bool IsDragging() const;

    // Must be implemented by any agent
    virtual std::optional<Move> GetMove(const Board &board);

protected:
    const CHESS_COLOR agentColor;

private:
    const std::string tag;
};

#endif //AGENT_H