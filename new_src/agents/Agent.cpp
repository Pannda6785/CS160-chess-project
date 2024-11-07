#include "Agent.h"

Agent::Agent(CHESS_COLOR agentColor) : agentColor(agentColor) {}

CHESS_COLOR Agent::GetColor() const {
    return agentColor;
}
    
std::optional<Position> Agent::GetSelectedPosition() const { 
    return std::nullopt; 
}

bool Agent::IsPromoting() const {
    return false;
}

int Agent::GetPromotingFile() const {
    // Is not expected to be called.
    return -1;
}

std::optional<Move> Agent::GetMove(const Board &board) {
    // Is not expected to be called
    return std::nullopt;
}