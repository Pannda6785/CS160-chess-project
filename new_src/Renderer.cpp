#include "Renderer.h"
#include "RenderUtilities.h"
#include "Properties.h"

Renderer renderer;

// TO DO: render the right stuffs in the end

void Renderer::SetBackgroundTexture(const Texture &texture) {
    backgroundTexture = texture;
}

void Renderer::SetPieceTextures(const std::map<std::string, Texture> &textures) {
    pieceTextures = textures;
}

void Renderer::RenderBackground() {
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

void Renderer::RenderLastMove(Move lastMove) {
    int x0 = Properties::GetBorderSize() + lastMove.fromPosition.j * Properties::GetCellSize();
    int y0 = Properties::GetBorderSize() + lastMove.fromPosition.i * Properties::GetCellSize();
    int x1 = Properties::GetBorderSize() + lastMove.toPosition.j * Properties::GetCellSize();
    int y1 = Properties::GetBorderSize() + lastMove.toPosition.i * Properties::GetCellSize();
    DrawRectangle(x0, y0, Properties::GetCellSize(), Properties::GetCellSize(), Color{144, 238, 144, 150});
    DrawRectangle(x1, y1, Properties::GetCellSize(), Properties::GetCellSize(), Color{144, 238, 144, 150});
}

void Renderer::RenderPieces(std::vector<const Piece*> pieces) {
    for (const Piece* piece : pieces) {
        int i = piece->GetPosition().i;
        int j = piece->GetPosition().j;
        int x = Properties::GetBorderSize() + j * Properties::GetCellSize() + Properties::GetCellSize() / 2;
        int y = Properties::GetBorderSize() + i * Properties::GetCellSize() + Properties::GetCellSize() / 2;
        Color color = piece->GetColor() == CHESS_WHITE ? PINK : GREEN;
        DrawCircle(x, y, 30, color);  
    }
}

void Renderer::RenderDraggingPiece(const Piece* piece) {
    Vector2 mousePosition = GetMousePosition();
    Color color = piece->GetColor() == CHESS_WHITE ? PINK : GREEN;
    DrawCircle(mousePosition.x, mousePosition.y, 30, color);  
}

void Renderer::RenderSelectedPosition(Position position) {
    int x = Properties::GetBorderSize() + position.j * Properties::GetCellSize();
    int y = Properties::GetBorderSize() + position.i * Properties::GetCellSize();
    DrawRectangle(x, y, Properties::GetCellSize(), Properties::GetCellSize(), Color{144, 238, 144, 150});
}

void Renderer::RenderPossibleMoves(std::vector<Move> possibleMoves) {
    for (Move move : possibleMoves) {
        int i = move.toPosition.i;
        int j = move.toPosition.j;
        int x = Properties::GetBorderSize() + j * Properties::GetCellSize() + Properties::GetCellSize() / 2;
        int y = Properties::GetBorderSize() + i * Properties::GetCellSize() + Properties::GetCellSize() / 2;
        DrawCircle(x, y, 10, GRAY);                 
    }
}

void Renderer::RenderPromotion(CHESS_COLOR color, int promotingFile) {
    int b = Properties::GetBorderSize();
    int c = Properties::GetCellSize();
    int x = b + promotingFile * c;
    if (color == CHESS_WHITE) {
        DrawRectangle(x, b, c, 4.5 * c, GOLD);
        DrawTextCen("Q", x + c / 2, b + c * 0.5, 35, PINK);
        DrawTextCen("N", x + c / 2, b + c * 1.5, 35, PINK);
        DrawTextCen("R", x + c / 2, b + c * 2.5, 35, PINK);
        DrawTextCen("B", x + c / 2, b + c * 3.5, 35, PINK);
        DrawTextCen("X", x + c / 2, b + c * 4.25, 20, GRAY);
    } else {
        DrawRectangle(x, b + c * 3.5, c, 4.5 * c, GOLD);
        DrawTextCen("Q", x + c / 2, b + c * 7.5, 35, GREEN);
        DrawTextCen("N", x + c / 2, b + c * 6.5, 35, GREEN);
        DrawTextCen("R", x + c / 2, b + c * 5.5, 35, GREEN);
        DrawTextCen("B", x + c / 2, b + c * 4.5, 35, GREEN);
        DrawTextCen("X", x + c / 2, b + c * 3.75, 20, GRAY);
    }
}