/*

This file provides basic utilities as an extension to the raylib library.

*/

#ifndef RENDER_UTILITIES_H
#define RENDER_UTILITIES_H

#include "raylib.h"

// Draws the text centered at a position (posX, posY)
void DrawTextCen(const char *text, int posX, int posY, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    int textX = posX - textWidth / 2;
    int textY = posY - fontSize / 2;  // The font size represents the height of the text
    DrawText(text, textX, textY, fontSize, color);
}

// Draws the text centered in the rectangle 
void DrawTextRec(const char *text, Rectangle rec, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    int textX = rec.x + (rec.width - textWidth) / 2;
    int textY = rec.y + (rec.height - fontSize) / 2;
    DrawText(text, textX, textY, fontSize, color);
}


#endif //RENDER_UTILITIES_H
