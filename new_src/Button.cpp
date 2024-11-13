#include "Button.h"
#include "RenderUtilities.h"

Button::Button() {}
Button::~Button() {
    UnloadTexture(texture); 
    UnloadSound(sound);  
    UnloadFont(font);
}

void Button::SetRec(Rectangle rec, Color recColor = LIGHTGRAY, Color hoveringColor = WHITE) {
    this->useRatio = false;
    this->rec = rec;
    this->recColor = recColor;
    this->hoveringColor = hoveringColor;
}

void Button::SetRatio(float rx, float dx, float ry, float dy, float rw, float dw, float rh, float dh, Color recColor = LIGHTGRAY, Color hoveringColor = WHITE) {
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

void Button::SetSound(Sound sound) {
    this->sound = sound;
}

void Button::Render() {
    // TO DO: should do some switching of state here, as well as handling the texture if applicable

    Rectangle rec = !useRatio ? this->rec : Rectangle{GetScreenWidth() * rx + dx, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};

    // Render the box
    if(texture.id == 0) {
        switch(state) {
            case HOVERING: {
                DrawRectangleRec(rec, {255, 255, 255, 100});
                break;
            }
            default: {
                DrawRectangleRec(rec, {0, 0, 0, 0});
                break;
            }
        }
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
            } else {
                state = HOVERING;
            }
        }
    } else {
        state = NONE;
    }
}