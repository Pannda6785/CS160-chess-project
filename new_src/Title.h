#include "raylib.h"
#include "Properties.h"

class Title {
public:
    void Run() {
        ClearBackground(RAYWHITE);
        DrawText("This is the main menu, press ENTER to play the game", 190, 200, 20, LIGHTGRAY);
        if (IsKeyPressed(KEY_ENTER)) {
            scene = GAMESCENE;
        }
    }
};