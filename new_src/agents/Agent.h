#include "../ChessUnits.h"
#include "../Board.h"

class Agent {
public:
    Agent(CHESS_COLOR agentColor) : agentColor(agentColor) {}
    CHESS_COLOR GetColor() const {
        return agentColor;
    }

    virtual std::optional<Move> GetMove(const Board &board);

private:
    const CHESS_COLOR agentColor;
    
};