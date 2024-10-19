#include "raylib.h"
#include "Properties.h"
#include "Title.h"
#include "Game.h"

int main() {
    // Init game window
    InitWindow(Properties::screenWidth, Properties::screenHeight, "CS160-chess-project");
    InitAudioDevice();

    // Load assets
    Properties::LoadSounds();
    Properties::LoadTextures();

    SCENE scene = TITLESCENE;
    Title title;
    Game game;

     while(!WindowShouldClose()) {
        BeginDrawing(); {
            switch(scene) {
                case TITLESCENE: {
                    title.Run();
                    scene = title.getScene();
                }; break;
                case GAMESCENE: {
                    game.Run();
                    scene = game.getScene();
                }; break;
                default: break;
            }
        } EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
}