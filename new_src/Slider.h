#ifndef SLIDER_H
#define SLIDER_H

#include "raylib.h"
#include <string>

class Slider {
public:
    Slider();
    ~Slider();

    // Process input
    void SetRec(Rectangle rec, Color recColor, Color progressColor, Color hoveringColor);
    void SetRatio(float rx, float dx, float ry, float dy, float rw, float dw, float rh, float dh, Color recColor, Color progressColor, Color hoveringColor);
    void SetSound(Sound sound);
    void SetProgressRatio(float progress);
    float Get();

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
    Color recColor = BLANK;
    Color hoveringColor = Color{255, 255, 255, 100};
    Sound sound = {};

    // dedicated for slider
    Rectangle subRec; // for better visual
    Rectangle progressRec; // showing % of figure
    const float sub = 5.0;
    float progress = 1.0;
    Color progressColor = Color{255, 109, 194, 255};

    void ClickedSound();
    void UpdateState();
};

#endif //SLIDER_H
