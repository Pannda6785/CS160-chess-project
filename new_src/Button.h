#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include <string>

class Button {
public:
    Button();
    ~Button();

    // Process input
    void SetRec(Rectangle rec, Color recColor);
    void SetRatio(float rx, float dx, float ry, float dy, float rw, float dw, float rh, float dh, Color recColor);
    void SetText(std::string text, int fontSize, Color textColor, Font font);
    void SetSound(Sound sound);

    void Render();
    bool Check();

private:
    enum BUTTON_STATE {
        NONE,
        HOVERING,
        HOLDING,
        CLICKED
    };
    BUTTON_STATE state;

    // Input figure
    Rectangle rec;
    bool useRatio = false;
    float rx, dx, ry, dy;
    float rw, dw, rh, dh;
    Color recColor = LIGHTGRAY;

    // Input properties
    std::string text = "";
    int fontSize = 0;
    Color textColor = GRAY;
    Font font = {};
    Sound sound = {};
    Texture texture = {};

    void ClickedSound();
    void UpdateState();
};

#endif //BUTTON_H
