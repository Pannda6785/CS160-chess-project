#include "Game.h"

void Game::Run() {
    nextScene = GAMESCENE;
    ClearBackground(RAYWHITE);
    DrawText("This is the game, enjoy!", 190, 200, 20, RED);
}


SCENE Game::getScene() {
    return nextScene;
}