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
    DrawTexturePro(Properties::skins["board"], (Rectangle) {0.0, 0.0, (float) Properties::skins["board"].width, (float) Properties::skins["board"].height}, 
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
        int y = Properties::GetBorderSize() + (i + 1) * Properties::GetCellSize() - Properties::GetCellSize() * Properties::skins[pieceName].height / Properties::skins[pieceName].width;
        DrawTexturePro(Properties::skins[pieceName], Rectangle{0, 0, (float) Properties::skins[pieceName].width, (float) Properties::skins[pieceName].height},
            Rectangle{(float) x, (float) y, (float) Properties::GetCellSize(), (float) Properties::GetCellSize() * Properties::skins[pieceName].height / Properties::skins[pieceName].width}, Vector2{0, 0}, 0, WHITE);              
    }
}

void Renderer::RenderDraggingPiece(const Piece* piece) {
    Vector2 mousePosition = GetMousePosition();
    std::string pieceName = (piece->GetColor() == CHESS_WHITE ? "w" : "b") + piece->GetTag();
    
    // the min-max is for the boundary. feel free to unlock the limit.
    int x = std::max(std::min((int) mousePosition.x, Properties::GetBorderSize() + 8 * Properties::GetCellSize()), Properties::GetBorderSize());
    x = x - Properties::GetCellSize() / 2;
    int y = std::max(std::min((int) mousePosition.y, Properties::GetBorderSize() + 8 * Properties::GetCellSize()), Properties::GetBorderSize());
    y = y - Properties::GetCellSize() * Properties::skins[pieceName].height / Properties::skins[pieceName].width / 2;
    
    DrawTexturePro(Properties::skins[pieceName], Rectangle{0, 0, (float) Properties::skins[pieceName].width, (float) Properties::skins[pieceName].height},
        Rectangle{(float) x, (float) y, (float) Properties::GetCellSize(), (float) Properties::GetCellSize() * Properties::skins[pieceName].height / Properties::skins[pieceName].width}, Vector2{0, 0}, 0, WHITE);              
}

void Renderer::RenderSelectedPosition(Position position, Color color) {
    int x = Properties::GetBorderSize() + position.j * Properties::GetCellSize();
    int y = Properties::GetBorderSize() + position.i * Properties::GetCellSize();
    DrawRectangle(x, y, Properties::GetCellSize(), Properties::GetCellSize(), color);
}

void Renderer::RenderPossibleMoves(std::vector<Move> possibleMoves) {
    for (Move move : possibleMoves) {
        int i = move.toPosition.i;
        int j = move.toPosition.j;
        int x = Properties::GetBorderSize() + j * Properties::GetCellSize();
        int y = Properties::GetBorderSize() + i * Properties::GetCellSize();

        switch(move.type) {
            // 'capture'
            case ATTACK: {
                DrawTexturePro(Properties::skins["capture"], Rectangle{0, 0, (float) Properties::skins["capture"].width, (float) Properties::skins["capture"].height},
                    Rectangle{(float) x, (float) y, (float) Properties::GetCellSize(), (float) Properties::GetCellSize()}, Vector2{0, 0}, 0, WHITE);              
            } break;
            // 'promotion'
            case PROMOTION: {
                DrawTexturePro(Properties::skins["promotion"], Rectangle{0, 0, (float) Properties::skins["promotion"].width, (float) Properties::skins["promotion"].height},
                    Rectangle{(float) x, (float) y, (float) Properties::GetCellSize(), (float) Properties::GetCellSize()}, Vector2{0, 0}, 0, WHITE);              
            } break;
            case ATTACK_AND_PROMOTION: {
                DrawTexturePro(Properties::skins["promotion"], Rectangle{0, 0, (float) Properties::skins["promotion"].width, (float) Properties::skins["promotion"].height},
                    Rectangle{(float) x, (float) y, (float) Properties::GetCellSize(), (float) Properties::GetCellSize()}, Vector2{0, 0}, 0, WHITE);              
            } break;
            // 'enpassant'
            case EN_PASSANT: {
                DrawTexturePro(Properties::skins["enpassant"], Rectangle{0, 0, (float) Properties::skins["enpassant"].width, (float) Properties::skins["enpassant"].height},
                    Rectangle{(float) x, (float) y, (float) Properties::GetCellSize(), (float) Properties::GetCellSize()}, Vector2{0, 0}, 0, WHITE);              
            } break;
            // 'move'
            default: {
                DrawTexturePro(Properties::skins["move"], Rectangle{0, 0, (float) Properties::skins["move"].width, (float) Properties::skins["move"].height},
                    Rectangle{(float) x, (float) y, (float) Properties::GetCellSize(), (float) Properties::GetCellSize()}, Vector2{0, 0}, 0, WHITE);              
            } break;
        }            
    }
}

void Renderer::RenderPromotion(CHESS_COLOR color, int promotingFile) {
    int b = Properties::GetBorderSize();
    int c = Properties::GetCellSize();
    int x = b + promotingFile * c;
    if (color == CHESS_WHITE) {
        DrawRectangle(x, b, c, 4.5 * c, GOLD);
        DrawTexturePro(Properties::skins["wQ"], Rectangle{0, 0, (float) Properties::skins["wQ"].width, (float) Properties::skins["wQ"].height},
            Rectangle{(float) x, (float) b + 1 * c - c * Properties::skins["wQ"].height / Properties::skins["wQ"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skins["wQ"].height / Properties::skins["wQ"].width}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skins["wN"], Rectangle{0, 0, (float) Properties::skins["wN"].width, (float) Properties::skins["wN"].height},
            Rectangle{(float) x, (float) b + 2 * c - c * Properties::skins["wN"].height / Properties::skins["wN"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skins["wN"].height / Properties::skins["wN"].width}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skins["wR"], Rectangle{0, 0, (float) Properties::skins["wR"].width, (float) Properties::skins["wR"].height},
            Rectangle{(float) x, (float) b + 3 * c - c * Properties::skins["wR"].height / Properties::skins["wR"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skins["wR"].height / Properties::skins["wR"].width}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skins["wB"], Rectangle{0, 0, (float) Properties::skins["wB"].width, (float) Properties::skins["wB"].height},
            Rectangle{(float) x, (float) b + 4 * c - c * Properties::skins["wB"].height / Properties::skins["wB"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skins["wB"].height / Properties::skins["wB"].width}, Vector2{0, 0}, 0, WHITE);
        DrawTextCen("x", x + c / 2, b + c * 4.25, 20, GRAY);         
    } else {
        DrawRectangle(x, b + c * 3.5, c, 4.5 * c, GOLD);
        DrawTexturePro(Properties::skins["bB"], Rectangle{0, 0, (float) Properties::skins["bB"].width, (float) Properties::skins["bB"].height},
            Rectangle{(float) x, (float) b + 5 * c - c * Properties::skins["bB"].height / Properties::skins["bB"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skins["bB"].height / Properties::skins["bB"].width}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skins["bR"], Rectangle{0, 0, (float) Properties::skins["bR"].width, (float) Properties::skins["bR"].height},
            Rectangle{(float) x, (float) b + 6 * c - c * Properties::skins["bR"].height / Properties::skins["bR"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skins["bR"].height / Properties::skins["bR"].width}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skins["bN"], Rectangle{0, 0, (float) Properties::skins["bN"].width, (float) Properties::skins["bN"].height},
            Rectangle{(float) x, (float) b + 7 * c - c * Properties::skins["bN"].height / Properties::skins["bN"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skins["bN"].height / Properties::skins["bN"].width}, Vector2{0, 0}, 0, WHITE);              
        DrawTexturePro(Properties::skins["bQ"], Rectangle{0, 0, (float) Properties::skins["bQ"].width, (float) Properties::skins["bQ"].height},
            Rectangle{(float) x, (float) b + 8 * c - c * Properties::skins["bQ"].height / Properties::skins["bQ"].width, (float) Properties::GetCellSize(),
            (float) c * Properties::skins["bQ"].height / Properties::skins["bQ"].width}, Vector2{0, 0}, 0, WHITE);              
        DrawTextCen("x", x + c / 2, b + c * 3.75, 20, GRAY);
    }
}

