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
    // Button(Rectangle rec, Color recColor, Texture texture, Sound sound, Font font, std::string text = "", int fontSize = 0, Color textColor = BLACK) : rec(rec), recColor(recColor), texture(texture), sound(sound), font(font), text(text), fontSize(fontSize), textColor(textColor) {}
    ~Button() {
        UnloadTexture(texture); 
        UnloadSound(sound);  
        UnloadFont(font);
    }

    void SetRec(Rectangle rec, Color recColor = LIGHTGRAY) {
        this->useRatio = false;
        this->rec = rec;
        this->recColor = recColor;
    }

    void SetRatio(float rx, float dx, float ry, float dy, float rw, float dw, float rh, float dh, Color recColor = LIGHTGRAY) {
        this->useRatio = true;
        this->rx = rx;
        this->dx = dx;
        this->ry = ry;
        this->dy = dy;
        this->rw = rw;
        this->dw = dw;
        this->rh = rh;
        this->dh = dh;
        this->recColor = recColor;
    }

    void SetText(std::string text, int fontSize = 0, Color textColor = GRAY, Font font = {}) {
        this->text = text;
        this->fontSize = fontSize;
        this->textColor = textColor;
        this->font = font;
    }

    void SetSound(Sound sound) {
        this->sound = sound;
    }

    void Render() {
        // TO DO: should do some switching of state here, as well as handling the texture if applicable
        
        Rectangle rec = !useRatio ? this->rec : Rectangle{GetScreenWidth() * rx + dx, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};

        // Render the box
        if(texture.id == 0) {
            DrawRectangleRec(rec, recColor);
        } else {
            DrawTexturePro(texture, (Rectangle) {0.0, 0.0, (float) texture.width, (float) texture.height}, rec, (Vector2) {0.0, 0.0}, 0.0, recColor);
        }

        // Render text in the box
        if(text != "") {
            if(font.texture.id == 0) {
                DrawTextRec(text.c_str(), rec, fontSize, textColor);
            }
            else DrawTextRecEx(font, text.c_str(), rec, fontSize, 2, LIME);
        }
    }

    bool Check() {
        UpdateState();
        if (state == CLICKED) ClickedSound();
        return state == CLICKED;
    }

    // void SetRec(Rectangle rec, Color recColor = LIGHTGRAY);
    // void SetRatio(double rx, double ry, double dx, double dy, double rw, double dw, double rh, double dh, Color recColor = LIGHTGRAY);
    // void SetText(std::string text, int fontSize = 0, Color textColor = GRAY, Font font = {});
    // void SetSound(Sound sound);

    // void Render();
    // bool Check(); // Returns true if the button is pressed

private:
    enum BUTTON_STATE {
        NONE,
        HOVERING,
        HOLDING,
        CLICKED
    };
    BUTTON_STATE state;

    Rectangle rec;
    bool useRatio = false;
    float rx, dx, ry, dy;
    float rw, dw, rh, dh;
    Color recColor = LIGHTGRAY;

    std::string text = "";
    int fontSize = 0;
    Color textColor = GRAY;
    Font font = {};

    Sound sound = {};
    Texture texture = {};

    void ClickedSound() {
        if (sound.frameCount != 0) {
            PlaySound(sound);
        }
    }

    void UpdateState() {
        Rectangle rec = !useRatio ? this->rec : Rectangle{GetScreenWidth() * rx + dx, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};
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

};

#endif //BUTTON_H
