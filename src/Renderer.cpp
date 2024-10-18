#include "raylib.h"
#include "pieces/Piece.h"
#include "Game.h"
#include "Properties.h"
#include "Renderer.h"

#include <algorithm>

void Renderer::Clear() {
    ClearBackground(WHITE);
}

void Renderer::RenderBackground() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int x = j * Properties::cell_size;
            int y = i * Properties::cell_size;

            Color cellColor = GetShadeColor(GetColorOfCell({i, j}));
            DrawRectangle(x, y, Properties::cell_size, Properties::cell_size, cellColor);
        }
    }
}

void Renderer::RenderPieces(const Board& board, const std::map<std::string, Texture>& textures) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* piece = board.At({i, j});

            if (piece != nullptr) {
                int x = j * Properties::cell_size;
                int y = i * Properties::cell_size;

                DrawTexture(textures.at(piece->GetName()), x, y, WHITE);
            }
        }
    }
}

void Renderer::RenderMovesSelectedPiece(const std::map<std::string, Texture>& textures, const std::vector<Move>& possibleMoves) {
    for (const Move& move : possibleMoves) {
        DrawTexture(
            textures.at(GetTextureNameFromMoveType(move.type)),
            move.position.j * Properties::cell_size,
            move.position.i * Properties::cell_size,
            WHITE
        );
    }
}

void Renderer::RenderGuideText() {
    int padding = 3;
    int characterSize = 10;

    // Render 1-8 numbers (rows).
    for (int i = 0; i < 8; i++) {
        Color textColor = GetShadeColor(Piece::GetInverseColor(GetColorOfCell({i, 0})));

        // Render text.
        int x = padding;
        int y = i * Properties::cell_size + padding;

        char text[2];
        text[0] = 49 + i;
        text[1] = 0;

        DrawText(text, x, y, 20, textColor);
    }

    // Render h-a characters (columns).
    for (int j = 0; j < 8; j++) {
        Color textColor = GetShadeColor(Piece::GetInverseColor(GetColorOfCell({7, j})));

        // Render text.
        int x = (j + 1) * Properties::cell_size - characterSize - padding;
        int y = Properties::screenHeight - characterSize * 1.75 - padding;

        char text[2];
        text[0] = 97 + (7 - j);
        text[1] = 0;

        DrawText(text, x, y, 20, textColor);
    }
}

void Renderer::RenderPromotionScreen(const std::map<std::string, Texture>& textures, PIECE_COLOR colorOfPeon) {
    DrawRectangle(0, 0, Properties::screenWidth, Properties::screenHeight, Color{0, 0, 0, 127});
    DrawText("Promotion", Properties::screenWidth / 2 - 98, Properties::screenHeight / 4, 40, WHITE);

    std::string prefix = colorOfPeon == PIECE_COLOR::C_WHITE ? "w" : "b";

    int textureY = Properties::cell_size * 3;
    int textY = Properties::cell_size * 4 + 5;

    // Draw queen.
    {
        DrawTexture(textures.at(prefix + "q"), Properties::cell_size * 2, textureY, WHITE);
        DrawText("Queen", Properties::cell_size * 2 + 9, textY, 20, WHITE);
    }

    // Draw rook.
    {
        DrawTexture(textures.at(prefix + "r"), Properties::cell_size * 3, textureY, WHITE);
        DrawText("Rook", Properties::cell_size * 3 + 14, textY, 20, WHITE);
    }

    // Draw bishop.
    {
        DrawTexture(textures.at(prefix + "b"), Properties::cell_size * 4, textureY, WHITE);
        DrawText("Bishop", Properties::cell_size * 4 + 7, textY, 20, WHITE);
    }

    // Draw knight.
    {
        DrawTexture(textures.at(prefix + "n"), Properties::cell_size * 5, textureY, WHITE);
        DrawText("Knight", Properties::cell_size * 5 + 9, textY, 20, WHITE);
    }
}

void Renderer::RenderEndScreen(GAME_STATE state) {
    DrawRectangle(0, 0, Properties::screenWidth, Properties::screenHeight, Color{0, 0, 0, 127});

    const char* text;

    if (state == S_WHITE_WINS) {
        text = "White wins";
    } else if (state == S_BLACK_WINS) {
        text = "Black wins";
    } else if (state == S_STALEMATE) {
        text = "Stalemate";
    }

    int textLength = MeasureText(text, 40);
    DrawText(text, Properties::screenWidth / 2 - textLength / 2, Properties::screenHeight / 2, 40, WHITE);
}

void Renderer::ChangeMouseCursor(const Board& board, const std::vector<Move>& possibleMoves, PIECE_COLOR turn, bool inPromotion) {
    Vector2 mousePosition = GetMousePosition();

    Position hoverPosition = {int(mousePosition.y) / Properties::cell_size, int(mousePosition.x) / Properties::cell_size};

    if (!inPromotion) {
        bool isHoveringOverPiece = board.At(hoverPosition) && board.At(hoverPosition)->color == turn;
        auto it = std::find_if(possibleMoves.begin(), possibleMoves.end(), [hoverPosition](const Move& m) {
            return m.position.i == hoverPosition.i && m.position.j == hoverPosition.j;
        });

        bool isHoveringOverMove = it != possibleMoves.end();

        // Set mouse to pointer if hovering over piece or hovering over move.
        if (isHoveringOverPiece || isHoveringOverMove) {
            SetMouseCursor(4);
        } else {
            SetMouseCursor(0);
        }
    } else {
        // If in promotion screen, also set mouse to pointer if hovering over the options.
        if (hoverPosition.i == 3 && hoverPosition.j >= 2 && hoverPosition.j <= 5) {
            SetMouseCursor(4);
        }
    }
}

std::string Renderer::GetTextureNameFromMoveType(MOVE_TYPE moveType) {
    switch (moveType) {
        case MOVE_TYPE::WALK:
        case MOVE_TYPE::DOUBLE_WALK:
        case MOVE_TYPE::ATTACK:
            return "move";

        case MOVE_TYPE::SHORT_CASTLING:
        case MOVE_TYPE::LONG_CASTLING:
            return "castling";

        case MOVE_TYPE::EN_PASSANT:
            return "enpassant";

        case MOVE_TYPE::PROMOTION:
        case MOVE_TYPE::ATTACK_AND_PROMOTION:
            return "promotion";
    }
}

Color Renderer::GetShadeColor(PIECE_COLOR color) {
    return color == PIECE_COLOR::C_WHITE ? Game::LIGHT_SHADE : Game::DARK_SHADE;
}

PIECE_COLOR Renderer::GetColorOfCell(const Position& cellPosition) {
    int startingColorInRow = cellPosition.i % 2 == 0 ? 0 : 1;
    int colorIndex = (startingColorInRow + cellPosition.j) % 2;

    return colorIndex == 0 ? PIECE_COLOR::C_WHITE : PIECE_COLOR::C_BLACK;
}