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

    void SetBackgroundTexture(const Texture &texture) {
        backgroundTexture = texture;
    }

    void SetPieceTextures(const std::map<std::string, Texture> &textures) {
        pieceTextures = textures;
    }

    void RenderBackground() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                int x = Properties::borderSize + j * Properties::cellSize;
                int y = Properties::borderSize + i * Properties::cellSize;

                int startingColorInRow = i % 2 == 0 ? 0 : 1;
                int colorIndex = (startingColorInRow + j) % 2;
                Color cellColor = colorIndex == 0 ? WHITE : BROWN;

                DrawRectangle(x, y, Properties::cellSize, Properties::cellSize, cellColor);
            }
        }   
    }

    void RenderPieces(const Board& board) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                const Piece* piece = board.GetPieceByPosition({i, j});
                if (piece != nullptr) {
                    int x = Properties::borderSize + j * Properties::cellSize + Properties::cellSize / 2;
                    int y = Properties::borderSize + i * Properties::cellSize + Properties::cellSize / 2;
                    Color color = piece->GetColor() == CHESS_WHITE ? PINK : GREEN;
                    DrawCircle(x, y, 30, color);                 
                }
            }
        }
    }

    void RenderSelectedPiece(Position position) {
        int x = Properties::borderSize + position.j * Properties::cellSize;
        int y = Properties::borderSize + position.i * Properties::cellSize;
        DrawRectangle(x, y, Properties::cellSize, Properties::cellSize, LIME);
    }

    void RenderPossibleMoves(std::vector<Move> possibleMoves) {
        for (Move move : possibleMoves) {
            int i = move.toPosition.i;
            int j = move.toPosition.j;
            int x = Properties::borderSize + j * Properties::cellSize + Properties::cellSize / 2;
            int y = Properties::borderSize + i * Properties::cellSize + Properties::cellSize / 2;
            DrawCircle(x, y, 10, GRAY);                 
        }
    }

private:

};

Renderer renderer;

#endif //RENDERER_H
