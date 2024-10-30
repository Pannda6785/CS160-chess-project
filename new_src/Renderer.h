#ifndef RENDERER_H
#define RENDERER_H

#include <map>

#include "raylib.h"
#include "Board.h"

class Renderer;
Renderer renderer;

class Renderer {
public:
    // TO DO

    std::map<std::string, Texture> pieceTextures;
    Texture backgroundTexture;

    void SetBackgroundTexture(const Texture &texture) {
        backgroundTexture = texture;
    }

    void SetPieceTextures(const std::map<std::string, Texture> &textures) {
        pieceTextures = textures;
    }

    void Clear() {

    }

    void RenderBackground() {

    }

    void RenderPieces(const Board& board) {

    }

    void RenderMovesSelectedPiece(const std::vector<Move>& possibleMoves) {

    }

    void RenderPromotionScreen(CHESS_COLOR colorOfPeonBeingPromoted) {

    }
 
    // static void Clear();
    // static void RenderBackground();
    // static void RenderPieces(const Board& board, const std::map<std::string, Texture>& textures);
    // static void RenderMovesSelectedPiece(const std::map<std::string, Texture>& textures, const std::vector<Move>& possibleMoves);
    // static void RenderGuideText();
    // static void RenderPromotionScreen(const std::map<std::string, Texture>& textures, PIECE_COLOR colorOfPeonBeingPromoted);
    // static void RenderEndScreen(GAME_STATE state);
    // static void ChangeMouseCursor(const Board& board, const std::vector<Move>& possibleMoves, PIECE_COLOR turn, bool inPromotion);

private:
    // static std::string GetTextureNameFromMoveType(MOVE_TYPE moveType);
    // static Color GetShadeColor(PIECE_COLOR color);
    // static PIECE_COLOR GetColorOfCell(const Position& cellPosition);
};


#endif //RENDERER_H
