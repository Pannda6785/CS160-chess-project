#ifndef INPUT_UTILITIES_H
#define INPUT_UTILITIES_H

#include "raylib.h"
#include "../Properties.h"
#include "../ChessUnits.h"

namespace InputUtilities {
    
    bool IsMouseInsideBoard() {
        Vector2 mousePosition = GetMousePosition();
        bool okX = Properties::borderSize < mousePosition.x && mousePosition.x < GetScreenHeight() - Properties::borderSize;
        bool okY = Properties::borderSize < mousePosition.y && mousePosition.x < GetScreenHeight() - Properties::borderSize;
        return okX && okY;
    }

    Position GetMouseChessPosition() { // assumes mouse is inside board
        Vector2 mousePosition = GetMousePosition();
        int i = (int(mousePosition.y) - Properties::borderSize) / Properties::cellSize;
        int j = (int(mousePosition.x) - Properties::borderSize) / Properties::cellSize;
        return Position{i, j};
    }

    bool IsMouseInsidePromotionSelectingZone() {
        Vector2 mousePosition = GetMousePosition();
        // TO DO: is mouse promotion zone
    }

    PIECE_TYPE GetMousePromotionPiece() {
        Vector2 mousePosition = GetMousePosition();
        // TO DO: where mouse promotion
    }
    
}

#endif //INPUT_UTILITIES_H