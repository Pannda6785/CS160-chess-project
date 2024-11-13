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
    bool IsDragging() const override;

    std::optional<Move> GetMove(const Board &board) override;

private:
    // the move to make, parts of decision are decided during different times
    bool isMoveFinalized;
    Move finalMove; 

    std::optional<Position> selectedPosition;

	bool isPromoting;
	int promotingFile;
    
    bool isDragging;

	void RenderCursor(const Board &board);
    void RegisterPressing(const Board &board);
    void RegisterReleasing(const Board &board);
};


#endif //MANUAL_AGENT_H