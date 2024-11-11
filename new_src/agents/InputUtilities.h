#ifndef INPUT_UTILITIES_H
#define INPUT_UTILITIES_H

#include "raylib.h"
#include "../Properties.h"
#include "../ChessUnits.h"

namespace InputUtilities {
    
    inline bool IsMouseInsideBoard() {
        Vector2 mousePosition = GetMousePosition();
        bool okX = Properties::GetBorderSize() < mousePosition.x && mousePosition.x < GetScreenHeight() - Properties::GetBorderSize();
        bool okY = Properties::GetBorderSize() < mousePosition.y && mousePosition.x < GetScreenHeight() - Properties::GetBorderSize();
        return okX && okY;
    }

    inline Position GetMouseChessPosition() { // assumes mouse is inside board
        Vector2 mousePosition = GetMousePosition();
        int i = (int(mousePosition.y) - Properties::GetBorderSize()) / Properties::GetCellSize();
        int j = (int(mousePosition.x) - Properties::GetBorderSize()) / Properties::GetCellSize();
        return Position{i, j};
    }

    inline bool IsMouseInsidePromotionSelectingZone(CHESS_COLOR color, int promotingFile) {
        Vector2 mousePosition = GetMousePosition();
        if (mousePosition.x < Properties::GetBorderSize() + Properties::GetCellSize() * promotingFile) return false;
        if (mousePosition.x > Properties::GetBorderSize() + Properties::GetCellSize() * (promotingFile + 1)) return false;
        if (color == CHESS_WHITE) {
            if (mousePosition.y < Properties::GetBorderSize()) return false;
            if (mousePosition.y > Properties::GetBorderSize() + 4.5 * Properties::GetCellSize()) return false;
        } else {
            if (mousePosition.y < Properties::GetBorderSize() + 3.5 * Properties::GetCellSize()) return false;
            if (mousePosition.y > Properties::GetBorderSize() + 8 * Properties::GetCellSize()) return false;
        }
        return true;
    }

    inline std::optional<PIECE_TYPE> GetMousePromotionPiece(CHESS_COLOR color, int promotingFile) { // assumes mouse is inside promotion choosing zone, returns nullopt if is in the promotion-canceling area
        Vector2 mousePosition = GetMousePosition();
        if (color == CHESS_WHITE) {
            if (mousePosition.y > Properties::GetBorderSize() + 4 * Properties::GetCellSize()) return std::nullopt;
            if (mousePosition.y > Properties::GetBorderSize() + 3 * Properties::GetCellSize()) return BISHOP;
            if (mousePosition.y > Properties::GetBorderSize() + 2 * Properties::GetCellSize()) return ROOK;
            if (mousePosition.y > Properties::GetBorderSize() + 1 * Properties::GetCellSize()) return KNIGHT;
        } else {
            if (mousePosition.y < Properties::GetBorderSize() + 4 * Properties::GetCellSize()) return std::nullopt;
            if (mousePosition.y < Properties::GetBorderSize() + 5 * Properties::GetCellSize()) return BISHOP;
            if (mousePosition.y < Properties::GetBorderSize() + 6 * Properties::GetCellSize()) return ROOK;
            if (mousePosition.y < Properties::GetBorderSize() + 7 * Properties::GetCellSize()) return KNIGHT;
        }
        return QUEEN;
    }
    
}

#endif //INPUT_UTILITIES_H