#ifndef RENDERER_H
#define RENDERER_H

#include <map>
#include <vector>

#include "raylib.h"
#include "Board.h"

class Renderer {
public:
    // Set textures
    void SetBackgroundTexture(const Texture &texture);
    void SetPieceTextures(const std::map<std::string, Texture> &textures);

    // Render stuffs
    void RenderBackground();
    void RenderLastMove(Move lastMove);
    void RenderPieces(std::vector<const Piece*> pieces);
    void RenderDraggingPiece(const Piece* piece);
    void RenderSelectedPosition(Position position);
    void RenderPossibleMoves(std::vector<Move> possibleMoves);
    void RenderPromotion(CHESS_COLOR color, int promotingFile);

private:
    std::map<std::string, Texture> pieceTextures;
    Texture backgroundTexture;

};

extern Renderer renderer;

#endif //RENDERER_H