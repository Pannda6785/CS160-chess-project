#include "Renderer.h"
#include "RenderUtilities.h"
#include "Properties.h"
#include <string>

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

void Renderer::RenderPieces(const Board& board) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            const Piece* piece = board.GetPieceByPosition({i, j});
            if (piece != nullptr) {
                /*
                // Render chess piece demo
                int xc = Properties::GetBorderSize() + j * Properties::GetCellSize() + Properties::GetCellSize() / 2;
                int yc = Properties::GetBorderSize() + i * Properties::GetCellSize() + Properties::GetCellSize() / 2;
                Color color = piece->GetColor() == CHESS_WHITE ? PINK : GREEN;
                */
                
                std::string pieceName = (piece->GetColor() == CHESS_WHITE ? "w" : "b") + piece->GetTag();
                int x = Properties::GetBorderSize() + j * Properties::GetCellSize();
                int y = Properties::GetBorderSize() + (i + 1) * Properties::GetCellSize() - Properties::GetCellSize() * Properties::skin1[pieceName].height / Properties::skin1[pieceName].width;
                DrawTexturePro(Properties::skin1[pieceName], Rectangle{0, 0, (float) Properties::skin1[pieceName].width, (float) Properties::skin1[pieceName].height},
                    Rectangle{(float) x, (float) y, (float) Properties::GetCellSize(), (float) Properties::GetCellSize() * Properties::skin1[pieceName].height / Properties::skin1[pieceName].width}, Vector2{0, 0}, 0, WHITE);              
            }
        }
    }
}

void Renderer::RenderSelectedPiece(Position position) {
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
        DrawTexturePro(Properties::skin1["wQ"], Rectangle{0, 0, (float)Properties::skin1["wQ"].width, (float)Properties::skin1["wQ"].height},
            Rectangle{(float) x, (float) b, (float) Properties::GetCellSize(), (float) Properties::GetCellSize()}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skin1["wR"], Rectangle{0, 0, (float)Properties::skin1["wR"].width, (float)Properties::skin1["wR"].height},
            Rectangle{(float) x, (float) b + c * 1, (float) Properties::GetCellSize(), (float) Properties::GetCellSize()}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skin1["wB"], Rectangle{0, 0, (float)Properties::skin1["wB"].width, (float)Properties::skin1["wB"].height},
            Rectangle{(float) x, (float) b + c * 2, (float) Properties::GetCellSize(), (float) Properties::GetCellSize()}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skin1["wN"], Rectangle{0, 0, (float)Properties::skin1["wN"].width, (float)Properties::skin1["wN"].height},
            Rectangle{(float) x, (float) b + c * 3, (float) Properties::GetCellSize(), (float) Properties::GetCellSize()}, Vector2{0, 0}, 0, WHITE);              
        DrawTextCen("x", x + c / 2, b + c * 4.25, 20, GRAY);
        // DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "X", x + c / 2, b + c * 4.25, 20, GRAY);
        // DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "GAY CHESS", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);
    } else {
        DrawRectangle(x, b + c * 3.5, c, 4.5 * c, GOLD);
        DrawTextCen("Q", x + c / 2, b + c * 7.5, 35, GREEN);
        DrawTextCen("N", x + c / 2, b + c * 6.5, 35, GREEN);
        DrawTextCen("R", x + c / 2, b + c * 5.5, 35, GREEN);
        DrawTextCen("B", x + c / 2, b + c * 4.5, 35, GREEN);
        DrawTextCen("X", x + c / 2, b + c * 3.75, 20, GRAY);
    }
}