#ifndef RENDERER_H
#define RENDERER_H

#include <map>

#include "raylib.h"
#include "Board.h"

class Renderer {
public:
    // TO DO: all about renderer
    // Set textures
    void Init();
    void SetBackgroundTexture(const Texture &texture);
    void SetPieceTextures(const std::map<std::string, Texture> &textures);

    // Render stuffs
    void RenderBackground();
    void RenderPieces(const Board& board);
    void RenderSelectedPiece(Position position);
    void RenderPossibleMoves(std::vector<Move> possibleMoves);

private:
    // Current boardTextures
    std::map<std::string, Texture> pieceTextures;
    Texture backgroundTexture;
};

extern Renderer renderer;

#endif //RENDERER_H
