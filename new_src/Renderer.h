#ifndef RENDERER_H
#define RENDERER_H

#include <map>

#include "raylib.h"
#include "Board.h"
#include "Properties.h"

class Renderer {
public:
    // TO DO: all about renderer

    std::map<std::string, Texture> pieceTextures;
    Texture backgroundTexture;

    // Set textures
    void SetBackgroundTexture(const Texture &texture);
    void SetPieceTextures(const std::map<std::string, Texture> &textures);

    // Render stuffs
    void RenderBackground();
    void RenderPieces(const Board& board);
    void RenderSelectedPiece(Position position);
    void RenderPossibleMoves(std::vector<Move> possibleMoves);

private:

};

extern Renderer renderer;

#endif //RENDERER_H
