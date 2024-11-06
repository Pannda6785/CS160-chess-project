/*

This file provides basic utilities as an extension to the raylib library.

*/

#ifndef RENDER_UTILITIES_H
#define RENDER_UTILITIES_H

#include "raylib.h"

// Draws the text centered at a position (posX, posY) without custom font
void DrawTextCen(const char *text, int posX, int posY, int fontSize, Color color) {
    int textWidth =  MeasureText(text, fontSize);;
    int textX = posX - textWidth / 2;
    int textY = posY - fontSize / 2;  // The font size represents the height of the text
    DrawText(text, textX, textY, fontSize, color);
}

// Draws the text centered at a position (posX, posY) with custom font
void DrawTextCenEx(Font font, const char *text, float posX, float posY, int fontSize, int spacing, Color color) {
    Vector2 pos = MeasureTextEx(font, text, fontSize, spacing);
    pos.x = posX - pos.x / 2;
    pos.y = posY - pos.y / 2;  // The font size represents the height of the text
    DrawTextEx(font, text, pos, fontSize, spacing, color);
}

// Draws the text centered in the rectangle without custom fonts
void DrawTextRec(const char *text, Rectangle rec, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    int textX = rec.x + (rec.width - textWidth) / 2;
    int textY = rec.y + (rec.height - fontSize) / 2;
    DrawText(text, textX, textY, fontSize, color);
}

// Draws the text centered in the rectangle with custom fonts
void DrawTextRecEx(Font font, const char *text, Rectangle rec, int fontSize,int spacing, Color color) {
    Vector2 pos = MeasureTextEx(font, text, fontSize, spacing);
    pos.x = rec.x + (rec.width - pos.x) / 2;
    pos.y = rec.y + (rec.height - pos.y) / 2;
    DrawTextEx(font, text, pos, fontSize, spacing, color);
}

#endif //RENDER_UTILITIES_H
