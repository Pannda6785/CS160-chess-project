#include "Agent.h"

Agent::Agent(CHESS_COLOR agentColor, std::string tag) : agentColor(agentColor), tag(tag) {}

CHESS_COLOR Agent::GetColor() const {
    return agentColor;
}

std::string Agent::GetTag() const {
    return tag;
}

void Agent::Init() {
    // by default, does nothing
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