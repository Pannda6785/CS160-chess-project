#include "ManualAgent.h"

#include "InputUtilities.h"

ManualAgent::ManualAgent(CHESS_COLOR agentColor) : Agent(agentColor) {
    selectedPosition = std::nullopt;
    isPromoting = false;
    promotingFile = -1;
}

std::optional<Position> ManualAgent::GetSelectedPosition() const {
    return selectedPosition;
}

bool ManualAgent::IsPromoting() const {
    return isPromoting;
}

int ManualAgent::GetPromotingFile() const {
    return promotingFile;
}

std::optional<Move> ManualAgent::GetMove(const Board &board) {
    RenderCursor(board);
    return _GetMove(board);
}

void ManualAgent::RenderCursor(const Board &board) {
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

    // Check promoting and hovering over the promotion zone
    if (isPromoting && InputUtilities::IsMouseInsidePromotionSelectingZone(agentColor, promotingFile)) {
        SetMouseCursor(4);
        return;
    }

    SetMouseCursor(0);
}

std::optional<Move> ManualAgent::_GetMove(const Board &board) {
    // No input needed to register
    if (!InputUtilities::IsMouseInsideBoard() || !IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        return std::nullopt;
    }

    Position clickedPosition = InputUtilities::GetMouseChessPosition();

    // Promotion handling foremost
    if (isPromoting) {
        if (InputUtilities::IsMouseInsidePromotionSelectingZone(agentColor, promotingFile) && InputUtilities::GetMousePromotionPiece(agentColor, promotingFile) != std::nullopt) { // valid promotion action
            PIECE_TYPE promotionPiece = InputUtilities::GetMousePromotionPiece(agentColor, promotingFile).value();
            promotionMove.promotionPiece = promotionPiece;
            isPromoting = false;
            selectedPosition = std::nullopt;
            return promotionMove;
        } else { // cancel the promotion, does not deselect the selected piece.
            isPromoting = false;
            return std::nullopt;
        }
    }

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
            // Check for promotion move
            if (move.type == PROMOTION || move.type == ATTACK_AND_PROMOTION) {
                isPromoting = true;
                promotingFile = move.toPosition.j;
                promotionMove = move;
                return std::nullopt;
            }
            // Normal move (including castling or enpassant)
            selectedPosition = std::nullopt;
            return move;
        }
    }

    // Chosen input does not make a valid move
    selectedPosition = std::nullopt;
    return std::nullopt;
}