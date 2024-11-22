#include "Button.h"
#include "RenderUtilities.h"
#include "Properties.h"

Button::Button() {}
Button::~Button() {
    UnloadTexture(texture); 
    UnloadTexture(hoveringTexture); 
    UnloadSound(sound);  
    UnloadFont(font);
}

void Button::SetRec(Rectangle rec, Color recColor = BLANK, Color hoveringColor = Color{255, 255, 255, 0}) {
    this->useRatio = false;
    this->rec = rec;
    this->recColor = recColor;
    this->hoveringColor = hoveringColor;
}

void Button::SetRatio(float rx, float dx, float ry, float dy, float rw, float dw, float rh, float dh, Color recColor = BLANK, Color hoveringColor = Color{255, 255, 255, 0}) {
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
    this->hoveringColor = hoveringColor;
}

void Button::SetText(std::string text, int fontSize = 0, Color textColor = GRAY, Font font = {}) {
    this->text = text;
    this->fontSize = fontSize;
    this->textColor = textColor;
    this->font = font;
}

void Button::SetHoveringText(std::string hoveringText, int fontSize = 0, Color textColor = GRAY, Font font = {}) {
    this->hoveringText = hoveringText;
    this->fontSize = fontSize;
    this->textColor = textColor;
    this->font = font;
}

void Button::SetSound(Sound sound) {
    this->sound = sound;
}

void Button::SetTexture(std::string name, std::string hoveringName){
    texture = Properties::elements[name];
    hoveringTexture = Properties::elements[hoveringName];
}

void Button::Render() {
    Rectangle rec = !useRatio ? this->rec : Rectangle{GetScreenWidth() * rx + dx, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};

    // Render the box
    if(state == HOVERING) DrawRectangleRec(rec, hoveringColor);
    else DrawRectangleRec(rec, recColor);
    if(texture.id != 0) {
        Rectangle textureRec = Rectangle{rec.x + rec.width / 2 - rec.height / 2, rec.y, rec.height, rec.height};
        if(state == HOVERING) DrawTexturePro(hoveringTexture, (Rectangle) {0.0, 0.0, (float) texture.width, (float) texture.height}, textureRec, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        else DrawTexturePro(texture, (Rectangle) {0.0, 0.0, (float) texture.width, (float) texture.height}, textureRec, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    }

    // Render text in the box
    if(state == HOVERING && hoveringText != "") {
        if(font.texture.id == 0) {
            DrawTextCursor(hoveringText.c_str(), fontSize, textColor);
        }
        else DrawTextCursorEx(font, hoveringText.c_str(), fontSize, 2, textColor);
    }
    if(text != "") {
        if(font.texture.id == 0) {
            DrawTextRec(text.c_str(), rec, fontSize, textColor);
        }
        else DrawTextRecEx(font, text.c_str(), rec, fontSize, 2, textColor);
    }
}

bool Button::Check() {
    UpdateState();
    if (state == CLICKED) ClickedSound();
    return state == CLICKED;
}

void Button::ClickedSound() {
    if (sound.frameCount != 0) {
        PlaySound(sound);
    }
}

void Button::UpdateState() {
    Rectangle rec = !useRatio ? this->rec : Rectangle{GetScreenWidth() * rx + dx, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};
    if (CheckCollisionPointRec(GetMousePosition(), rec)) {
        if (state == HOLDING && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            state = CLICKED;
        } else {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                state = HOLDING;
            } else if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                state = HOVERING;
            }
        }
    } else {
        state = NONE;
    }
}