#ifndef INPUT_UTILITIES_H
#define INPUT_UTILITIES_H

#include "raylib.h"
#include "Properties.h"
#include "ChessUnits.h"
#include "pieces/Piece.h"

namespace InputUtilities {
    
    bool IsMouseInsideBoard() {
        Vector2 mousePosition = GetMousePosition();
        return mousePosition.x < GetScreenHeight();
    }

    Position GetMouseChessPosition() {
        Vector2 mousePosition = GetMousePosition();
        int i = (int(mousePosition.y) - Properties::borderSize) / Properties::cellSize;
        int j = (int(mousePosition.x) - Properties::borderSize) / Properties::cellSize;
        return Position{i, j};
    }

    bool IsMouseInsidePromotionSelectingZone() {
        Vector2 mousePosition = GetMousePosition();
        // TO DO: is mouse promotion zone
    }

    Piece* GetMousePromotionPiece() {
        Vector2 mousePosition = GetMousePosition();
        // TO DO: where mouse promotion
    }
    
}

#endif //INPUT_UTILITIES_H