#ifndef MANUAL_AGENT_H
#define MANUAL_AGENT_H

#include "Agent.h"
#include "InputUtilities.h"

class ManualAgent : public Agent {
public:
    ManualAgent(CHESS_COLOR agentColor) : Agent(agentColor) {
		selectedPosition = std::nullopt;
	}

    std::optional<Move> GetMove(const Board &board) override {
		RenderCursor(board);
		return _GetMove(board);
    }

	std::optional<Position> GetSelectedPosition() const override {
		return selectedPosition;
	}

private:
    std::optional<Position> selectedPosition;
    
	std::optional<Move> _GetMove(const Board &board) {
        // No input needed to register
        if (!InputUtilities::IsMouseInsideBoard() || !IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return std::nullopt;
        }

		Position clickedPosition = InputUtilities::GetMouseChessPosition();

		// Selecting an allied piece
		const Piece* clickedPiece = board.GetPieceByPosition(clickedPosition);
		if (clickedPiece != nullptr && clickedPiece->GetColor() == agentColor) { 
			// TO DO: chessAudio.PlayPieceSelectSound();
			selectedPosition = clickedPosition;

			return std::nullopt;
		} 
		
		// No piece selected (and by above gate, is not trying to select a valid piece either)
		if (selectedPosition == std::nullopt) {
			return std::nullopt;
		}

		// By here, previously a piece is selected and now is not selecting an allied piece. Which means player should be trying to choose a valid move here
		const Piece* selectedPiece = board.GetPieceByPosition(selectedPosition.value());
		for (Move move : board.GetPossibleMoves(selectedPiece)) {
			if (clickedPosition == move.toPosition) {
				// TO DO: Promotion handling
				selectedPosition = std::nullopt;
				return move;
			}
		}

		// Chosen input does not make a valid move
		selectedPosition = std::nullopt;
		return std::nullopt;
	}

	void RenderCursor(const Board &board) {
		// Not interacting with game, so no need to update
		if (!InputUtilities::IsMouseInsideBoard()) return;

		Position hoveringPosition = InputUtilities::GetMouseChessPosition();

		// Check hovering over an allied piece (trying to select a piece)
		const Piece* hoveringPiece = board.GetPieceByPosition(hoveringPosition);
		if (hoveringPiece != nullptr && hoveringPiece->GetColor() == agentColor) {
			SetMouseCursor(4);
			return;
		}

		// Check if a piece is previously selected and now selecting its valid move
		if (selectedPosition != std::nullopt) {
			const Piece* selectedPiece = board.GetPieceByPosition(selectedPosition.value());
			for (Move move : board.GetPossibleMoves(selectedPiece)) {
				if (hoveringPosition == move.toPosition) {
					SetMouseCursor(4);
					return;
				}
			}
		}

		SetMouseCursor(0);
	}
};


#endif //MANUAL_AGENT_H