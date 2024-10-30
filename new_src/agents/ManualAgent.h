#ifndef MANUAL_AGENT_H
#define MANUAL_AGENT_H

#include "Agent.h"

class ManualAgent : public Agent {
    
        // if (InputUtilities::IsMouseInsideBoard() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        //     Position clickedPosition = InputUtilities::GetMouseChessPosition();
        //     Piece* clickedPiece = board.GetPieceByPosition(clickedPosition);

        //     if (clickedPiece != nullptr && clickedPiece->GetColor() == WhoseTurn()) { // Selecting a allied piece
        //         chessAudio.PlayPieceSelectSound();
        //         selectedPiece = clickedPiece;
        //     } else {
        //         if selectedPiece == nullptr
        //         or board.GetMove(selectedPiece, clickedPosition) == nullptr
                
        //     }

        //     // Select piece.
        //     if (clickedPiece != nullptr && clickedPiece->color == turn) {
        //         PlaySound(Properties::sounds["click"]);
        //         selectedPiece = clickedPiece;
        //     } else {
        //         // Do movement.
        //         Move* desiredMove = GetMoveAtPosition(clickedPosition);

        //         if (desiredMove && selectedPiece != nullptr) {
        //             DoMoveOnBoard(*desiredMove);
        //         } else {
        //             PlaySound(Properties::sounds["clickCancel"]);
        //         }

        //         // Piece must still be selected to render promotion screen.
        //         if (!desiredMove ||
        //         (desiredMove->type != MOVE_TYPE::PROMOTION &&
        //             desiredMove->type != MOVE_TYPE::ATTACK_AND_PROMOTION)
        //         ) {
        //             selectedPiece = nullptr;
        //         }
        //     }
        // }
};


#endif //MANUAL_AGENT_H