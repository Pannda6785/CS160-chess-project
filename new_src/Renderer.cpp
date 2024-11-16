#include "Renderer.h"
#include "RenderUtilities.h"
#include "Properties.h"
#include <string>
#include <algorithm>

Renderer renderer;

// TO DO: render the right stuffs in the end

void Renderer::SetBackgroundTexture(const Texture &texture) {
    backgroundTexture = texture;
}

void Renderer::SetPieceTextures(const std::map<std::string, Texture> &textures) {
    pieceTextures = textures;
}

void Renderer::RenderBackground() {
    DrawTexturePro(Properties::skin1["board"], (Rectangle) {0.0, 0.0, (float) Properties::skin1["board"].width, (float) Properties::skin1["board"].height}, 
                (Rectangle) {(float) Properties::GetBorderSize(), (float) Properties::GetBorderSize(), (float) 8 * Properties::GetCellSize(), (float) 8 * Properties::GetCellSize()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int x = Properties::GetBorderSize() + j * Properties::GetCellSize();
            int y = Properties::GetBorderSize() + i * Properties::GetCellSize();

            int startingColorInRow = i % 2 == 0 ? 0 : 1;
            int colorIndex = (startingColorInRow + j) % 2;
            Color cellColor = colorIndex == 0 ? Color{255, 255, 255, 100} : Color{0, 0, 0, 100};

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

void Renderer::RenderDraggingPiece(const Piece* piece) {
    Vector2 mousePosition = GetMousePosition();
    std::string pieceName = (piece->GetColor() == CHESS_WHITE ? "w" : "b") + piece->GetTag();
    
    // the min-max is for the boundary. feel free to unlock the limit.
    int x = std::max(std::min((int) mousePosition.x, Properties::GetBorderSize() + 8 * Properties::GetCellSize()), Properties::GetBorderSize());
    x = x - Properties::GetCellSize() / 2;
    int y = std::max(std::min((int) mousePosition.y, Properties::GetBorderSize() + 8 * Properties::GetCellSize()), Properties::GetBorderSize());
    y = y - Properties::GetCellSize() * Properties::skin1[pieceName].height / Properties::skin1[pieceName].width / 2;
    
    DrawTexturePro(Properties::skin1[pieceName], Rectangle{0, 0, (float) Properties::skin1[pieceName].width, (float) Properties::skin1[pieceName].height},
        Rectangle{(float) x, (float) y, (float) Properties::GetCellSize(), (float) Properties::GetCellSize() * Properties::skin1[pieceName].height / Properties::skin1[pieceName].width}, Vector2{0, 0}, 0, WHITE);              
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
        DrawTexturePro(Properties::skin1["wQ"], Rectangle{0, 0, (float) Properties::skin1["wQ"].width, (float) Properties::skin1["wQ"].height},
            Rectangle{(float) x, (float) b + 1 * c - c * Properties::skin1["wQ"].height / Properties::skin1["wQ"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skin1["wQ"].height / Properties::skin1["wQ"].width}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skin1["wR"], Rectangle{0, 0, (float) Properties::skin1["wR"].width, (float) Properties::skin1["wR"].height},
            Rectangle{(float) x, (float) b + 2 * c - c * Properties::skin1["wR"].height / Properties::skin1["wR"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skin1["wR"].height / Properties::skin1["wR"].width}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skin1["wB"], Rectangle{0, 0, (float) Properties::skin1["wB"].width, (float) Properties::skin1["wB"].height},
            Rectangle{(float) x, (float) b + 3 * c - c * Properties::skin1["wB"].height / Properties::skin1["wB"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skin1["wB"].height / Properties::skin1["wB"].width}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skin1["wN"], Rectangle{0, 0, (float) Properties::skin1["wN"].width, (float) Properties::skin1["wN"].height},
            Rectangle{(float) x, (float) b + 4 * c - c * Properties::skin1["wN"].height / Properties::skin1["wN"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skin1["wN"].height / Properties::skin1["wN"].width}, Vector2{0, 0}, 0, WHITE);
        DrawTextCen("x", x + c / 2, b + c * 4.25, 20, GRAY);         
    } else {
        DrawRectangle(x, b + c * 3.5, c, 4.5 * c, GOLD);
        DrawTexturePro(Properties::skin1["bN"], Rectangle{0, 0, (float) Properties::skin1["bN"].width, (float) Properties::skin1["bN"].height},
            Rectangle{(float) x, (float) b + 5 * c - c * Properties::skin1["bN"].height / Properties::skin1["bN"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skin1["bN"].height / Properties::skin1["bN"].width}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skin1["bB"], Rectangle{0, 0, (float) Properties::skin1["bB"].width, (float) Properties::skin1["bB"].height},
            Rectangle{(float) x, (float) b + 6 * c - c * Properties::skin1["bB"].height / Properties::skin1["bB"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skin1["bB"].height / Properties::skin1["bB"].width}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skin1["bR"], Rectangle{0, 0, (float) Properties::skin1["bR"].width, (float) Properties::skin1["bR"].height},
            Rectangle{(float) x, (float) b + 7 * c - c * Properties::skin1["bR"].height / Properties::skin1["bR"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skin1["bR"].height / Properties::skin1["bR"].width}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skin1["bQ"], Rectangle{0, 0, (float) Properties::skin1["bQ"].width, (float) Properties::skin1["bQ"].height},
            Rectangle{(float) x, (float) b + 8 * c - c * Properties::skin1["bQ"].height / Properties::skin1["bQ"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skin1["bQ"].height / Properties::skin1["bQ"].width}, Vector2{0, 0}, 0, WHITE);              
        DrawTextCen("x", x + c / 2, b + c * 3.75, 20, GRAY);
    }
}