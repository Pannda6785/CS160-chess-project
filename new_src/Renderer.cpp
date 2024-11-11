#include "Renderer.h"
#include "Properties.h"

Renderer renderer;

void Renderer::Init() {
    // TO DO: add assets
}

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

void Renderer::RenderPieces(const Board& board) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            const Piece* piece = board.GetPieceByPosition({i, j});
            if (piece != nullptr) {
                int x = Properties::GetBorderSize() + j * Properties::GetCellSize() + Properties::GetCellSize() / 2;
                int y = Properties::GetBorderSize() + i * Properties::GetCellSize() + Properties::GetCellSize() / 2;
                Color color = piece->GetColor() == CHESS_WHITE ? PINK : GREEN;
                DrawTexturePro(Properties::elements["gameBackGround"], Rectangle{0, 0, (float)Properties::elements["gameBackGround"].width, (float)Properties::elements["gameBackGround"].height},
                    Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, Vector2{0, 0}, 0, WHITE);                 
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