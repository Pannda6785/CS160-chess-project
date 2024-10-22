#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include "RenderUtilities.h"
#include <string>

class Button {
public:
    Button() {}
    Button(Rectangle rec, Color recColor, std::string text = "", int fontSize = 0, Color textColor = BLACK) : rec(rec), recColor(recColor), text(text), fontSize(fontSize), textColor(textColor) {}
    Button(Rectangle rec, Color recColor, Sound sound, std::string text = "", int fontSize = 0, Color textColor = BLACK) : rec(rec), recColor(recColor), sound(sound), text(text), fontSize(fontSize), textColor(textColor) {}
    ~Button() {
        UnloadTexture(texture); 
        UnloadSound(sound);  
    }

    // Renders the button and returns true if the button is pressed
    bool Check() {
        UpdateState();
        Render();
        return state == CLICKED;
    }

private:
    enum BUTTON_STATE {
        NONE,
        HOVERING,
        HOLDING,
        CLICKED
    };
    BUTTON_STATE state;

    Rectangle rec = {};
    Color recColor = LIGHTGRAY;

    std::string text = "";
    int fontSize = 0;
    Color textColor = GRAY;

    Sound sound = {};
    Texture2D texture = {};
    
    void UpdateState() {
        if (CheckCollisionPointRec(GetMousePosition(), rec)) {
            if (state == HOLDING && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                state = CLICKED;
                if (sound.frameCount != 0) {
                    PlaySound(sound);
                }
            } else {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    state = HOLDING;
                } else {
                    state = HOVERING;
                }
            }
        } else {
            state = NONE;
        }
    }

    void Render() {
        // TO DO: should do some switching of state here, as well as handling the texture if applicable
        DrawRectangleRec(rec, recColor);
        DrawTextRec(text.c_str(), rec, fontSize, textColor);
    }

};

#endif //BUTTON_H
