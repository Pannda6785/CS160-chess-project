#ifndef INPUT_UTILITIES_H
#define INPUT_UTILITIES_H

#include "raylib.h"
#include "../Properties.h"
#include "../ChessUnits.h"

namespace InputUtilities {
    
    bool IsMouseInsideBoard() {
        Vector2 mousePosition = GetMousePosition();
        bool okX = Properties::GetBorderSize() < mousePosition.x && mousePosition.x < GetScreenHeight() - Properties::GetBorderSize();
        bool okY = Properties::GetBorderSize() < mousePosition.y && mousePosition.x < GetScreenHeight() - Properties::GetBorderSize();
        return okX && okY;
    }

    Position GetMouseChessPosition() { // assumes mouse is inside board
        Vector2 mousePosition = GetMousePosition();
        int i = (int(mousePosition.y) - Properties::GetBorderSize()) / Properties::GetCellSize();
        int j = (int(mousePosition.x) - Properties::GetBorderSize()) / Properties::GetCellSize();
        return Position{i, j};
    }

    bool IsMouseInsidePromotionSelectingZone() {
        Vector2 mousePosition = GetMousePosition();
        // TO DO: is mouse promotion zone
        return false;
    }

    std::optional<PIECE_TYPE> GetMousePromotionPiece() { // assumes mouse is inside board, returns nullopt if is in the promotion-canceling area
        Vector2 mousePosition = GetMousePosition();
        // TO DO: where mouse promotion
        return std::nullopt;
    }
    
}

#endif //INPUT_UTILITIES_H