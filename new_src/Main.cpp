#include "raylib.h"
#include "Properties.h"
#include "TitleScene.h"
#include "GameScene.h"

int main() {
    // Init game window
    InitWindow(Properties::screenWidth, Properties::screenHeight, "CS160-chess-project");
    InitAudioDevice();
    SetTargetFPS(60);

    // Load assets
    Properties::LoadSounds();
    Properties::LoadTextures();

    // Variables initialization
    scene = TITLE_SCENE;
    SCENE lastScene = EXIT;
    TitleScene titleScene;
    GameScene gameScene;

    // Main game loop
    while(!WindowShouldClose() && scene != EXIT) {
        BeginDrawing(); {
            switch(scene) {
                case TITLE_SCENE: {
                    if (scene != lastScene) titleScene.Init(); // init the scene if entering the scene
                    titleScene.Run();
                }; break;
                case GAME_SCENE: {
                    if (scene != lastScene) gameScene.Init(); // init the scene if entering the scene
                    gameScene.Run();
                }; break;
                default: break;
            }
        } EndDrawing();
        lastScene = scene;
    }

    // Deinit game window
    CloseWindow();
    CloseAudioDevice();
}