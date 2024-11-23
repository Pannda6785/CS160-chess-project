#include "ManualAgent.h"

#include "InputUtilities.h"

ManualAgent::ManualAgent(CHESS_COLOR agentColor) : Agent(agentColor, "Human") {}

void ManualAgent::Init() {
    isMoveFinalized = false;
    selectedPosition = std::nullopt;
    isPromoting = false;
    isDragging = false;
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

bool ManualAgent::IsDragging() const {
    return isDragging;
}

std::optional<Move> ManualAgent::GetMove(const Board &board) {
    RenderCursor(board);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        RegisterPressing(board);
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        RegisterReleasing(board);
    }
    if (isMoveFinalized) {
        Init();
        SetMouseCursor(0);
        return finalMove;
    } else {
        return std::nullopt;
    }
}

void ManualAgent::RenderCursor(const Board &board) {
    // Not interacting with game, so no need to update
    if (!InputUtilities::IsMouseInsideBoard()) return;

    if (isDragging) { // Dragging uses the pointed hand cursor
        SetMouseCursor(4);
        return;
    }

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

void ManualAgent::RegisterPressing(const Board &board) {
    if (!InputUtilities::IsMouseInsideBoard()) return;
    Position clickedPosition = InputUtilities::GetMouseChessPosition();

    // Check promotion
    if (isPromoting) {
        if (InputUtilities::IsMouseInsidePromotionSelectingZone(agentColor, promotingFile) && InputUtilities::GetMousePromotionPiece(agentColor, promotingFile) != std::nullopt) { // valid promotion action
            PIECE_TYPE promotionPiece = InputUtilities::GetMousePromotionPiece(agentColor, promotingFile).value();
            finalMove.promotionPiece = promotionPiece;
            isMoveFinalized = true;
        } else { // cancel the promotion, does not deselect the selected piece.
            isPromoting = false;
        }
        return;
    }

    // Check selecting an allied piece
    const Piece* clickedPiece = board.GetPieceByPosition(clickedPosition);
    if (clickedPiece != nullptr && clickedPiece->GetColor() == agentColor) { // valid allied piece selected
        // TO DO: chessAudio.PlayPieceSelectSound();
        PlaySound(Properties::sounds["move"]);
        selectedPosition = clickedPosition;
        isDragging = true;
        return;
    }

    // Did not select an allied piece nor is promoting. So if no position is selected, should do nothing 
    if (selectedPosition == std::nullopt) {
        return;
    }

    // Check NOT deselecting
    const Piece* selectedPiece = board.GetPieceByPosition(selectedPosition.value());
    for (Move move : board.GetPossibleMoves(selectedPiece)) {
        if (clickedPosition == move.toPosition) {
            return;
        }
    }

    // Deselect
    selectedPosition = std::nullopt;
}

void ManualAgent::RegisterReleasing(const Board &board) {
    isDragging = false;
    if (!InputUtilities::IsMouseInsideBoard()) return;
    Position droppingPosition = InputUtilities::GetMouseChessPosition();
    
    // No piece selected
    if (selectedPosition == std::nullopt) {
        return;
    }

    // By here, previously a piece is selected. Which means player should be trying to choose a valid move here (by dropping the piece).
    const Piece* selectedPiece = board.GetPieceByPosition(selectedPosition.value());
    for (Move move : board.GetPossibleMoves(selectedPiece)) {
        if (droppingPosition == move.toPosition) {
            // Check for promotion move
            if (move.type == PROMOTION || move.type == ATTACK_AND_PROMOTION) {
                isPromoting = true;
                promotingFile = move.toPosition.j;
                finalMove = move;
                return;
            }
            // Normal move (including castling or enpassant)
            selectedPosition = std::nullopt;
            finalMove = move;
            isMoveFinalized = true;
            return;
        }
    }
}