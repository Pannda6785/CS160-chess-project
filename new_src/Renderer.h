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
                int x = Properties::GetBorderSize() + j * Properties::GetCellSize();
                int y = Properties::GetBorderSize() + i * Properties::GetCellSize();

                int startingColorInRow = i % 2 == 0 ? 0 : 1;
                int colorIndex = (startingColorInRow + j) % 2;
                Color cellColor = colorIndex == 0 ? WHITE : BROWN;

                DrawRectangle(x, y, Properties::GetCellSize(), Properties::GetCellSize(), cellColor);
            }
        }   
    }

    void RenderPieces(const Board& board) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                const Piece* piece = board.GetPieceByPosition({i, j});
                if (piece != nullptr) {
                    int x = Properties::GetBorderSize() + j * Properties::GetCellSize() + Properties::GetCellSize() / 2;
                    int y = Properties::GetBorderSize() + i * Properties::GetCellSize() + Properties::GetCellSize() / 2;
                    Color color = piece->GetColor() == CHESS_WHITE ? PINK : GREEN;
                    DrawCircle(x, y, 30, color);                 
                }
            }
        }
    }

    void RenderSelectedPiece(Position position) {
        int x = Properties::GetBorderSize() + position.j * Properties::GetCellSize();
        int y = Properties::GetBorderSize() + position.i * Properties::GetCellSize();
        DrawRectangle(x, y, Properties::GetCellSize(), Properties::GetCellSize(), Color{144, 238, 144, 150});
    }

    void RenderPossibleMoves(std::vector<Move> possibleMoves) {
        for (Move move : possibleMoves) {
            int i = move.toPosition.i;
            int j = move.toPosition.j;
            int x = Properties::GetBorderSize() + j * Properties::GetCellSize() + Properties::GetCellSize() / 2;
            int y = Properties::GetBorderSize() + i * Properties::GetCellSize() + Properties::GetCellSize() / 2;
            DrawCircle(x, y, 10, GRAY);                 
        }
    }

private:

};

inline Renderer renderer;

#endif //RENDERER_H
