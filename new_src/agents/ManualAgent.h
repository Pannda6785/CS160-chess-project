#ifndef MANUAL_AGENT_H
#define MANUAL_AGENT_H

#include "Agent.h"

class ManualAgent : public Agent {
public:
    ManualAgent(CHESS_COLOR agentColor);

    void Init() override;

    std::optional<Position> GetSelectedPosition() const override;
    bool IsPromoting() const override; 
    int GetPromotingFile() const override;

    std::optional<Move> GetMove(const Board &board) override;

private:
    std::optional<Position> selectedPosition;
	bool isPromoting;
	int promotingFile;
    Move promotionMove;
    
	std::optional<Move> _GetMove(const Board &board);
	void RenderCursor(const Board &board);

};


#endif //MANUAL_AGENT_H