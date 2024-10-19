#include "Title.h"

void Title::Run() {
    ClearBackground(RAYWHITE);
    DrawText("This is the main menu, press ENTER to play the game", 190, 200, 20, LIGHTGRAY);
    nextScene = TITLESCENE;
    if (IsKeyPressed(KEY_ENTER)) {
        nextScene = GAMESCENE;
    }
}

SCENE Title::getScene() {
    return nextScene;
}