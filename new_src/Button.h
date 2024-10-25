#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include "RenderUtilities.h"
#include <string>

class Button {
public:
    Button() {}
    // Button(Rectangle rec, Color recColor, std::string text = "", int fontSize = 0, Color textColor = BLACK) : rec(rec), recColor(recColor), text(text), fontSize(fontSize), textColor(textColor) {}
    // Button(Rectangle rec, Color recColor, Sound sound, std::string text = "", int fontSize = 0, Color textColor = BLACK) : rec(rec), recColor(recColor), sound(sound), text(text), fontSize(fontSize), textColor(textColor) {}
    Button(Rectangle rec, Color recColor, Texture texture, Sound sound, Font font, std::string text = "", int fontSize = 0, Color textColor = BLACK) : rec(rec), recColor(recColor), texture(texture), sound(sound), font(font), text(text), fontSize(fontSize), textColor(textColor) {}
    ~Button() {
        UnloadTexture(texture); 
        UnloadSound(sound);  
        UnloadFont(font);
    }

    // Renders the button and returns true if the button is pressed
    bool Check() {
        UpdateState();
        Render();
        if (state == CLICKED) ClickedSound();
        return state == CLICKED;
    }

    void UpdateRec(Rectangle newRec) {
        rec = newRec;
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
    Texture texture = {};
    Font font = {};
    
    void UpdateState() {
        if (CheckCollisionPointRec(GetMousePosition(), rec)) {
            if (state == HOLDING && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                state = CLICKED;
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
        
        // Render the box
        if(texture.id == 0) {
            DrawRectangleRec(rec, recColor);
        }
        else {
            DrawTexturePro(texture, (Rectangle) {0.0, 0.0, (float) texture.width, (float) texture.height}, rec, (Vector2) {0.0, 0.0}, 0.0, recColor);
        }

        // Render text in the box
        if(font.texture.id == 0) {
            DrawTextRec(text.c_str(), rec, fontSize, textColor);
        }
        else DrawTextRecEx(font, text.c_str(), rec, fontSize, 2, LIME);
    }

    void ClickedSound() {
        if (sound.frameCount != 0) {
            PlaySound(sound);
        }
    }

};

#endif //BUTTON_H
