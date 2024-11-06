#include "raylib.h"
#include "Properties.h"
#include "TitleScene.h"
#include "GameScene.h"

int main() {
    // Init game window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // temporary disable
    InitWindow(Properties::GetInitialScreenWidth(), Properties::GetInitialScreenHeight(), "CS160-chess-project");
    InitAudioDevice();
    SetTargetFPS(60);

    // Load assets
    Properties::LoadSounds();
    Properties::LoadTextures();
    Properties::LoadElements();
    Properties::LoadFonts();

    // Variables initialization
    scene = TITLE_SCENE;
    isSceneChanged = true;
    TitleScene titleScene;
    GameScene gameScene;

    // Main game loop
    while(!WindowShouldClose() && scene != EXIT) {
        if (IsKeyPressed(KEY_SPACE)) {
            if (!IsWindowFullscreen()) {
                int monitor = GetCurrentMonitor();
                SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
                ToggleFullscreen();
            } else {
                ToggleFullscreen();
                SetWindowSize(Properties::GetInitialScreenWidth(), Properties::GetInitialScreenHeight());
            }
        }
        BeginDrawing(); {
            switch(scene) {
                case TITLE_SCENE: {
                    if (isSceneChanged) titleScene.Init(), isSceneChanged = false; // init the scene if entering the scene
                    titleScene.Run();
                }; break;
                case GAME_SCENE: {
                    if (isSceneChanged) gameScene.Init(), isSceneChanged = false; // init the scene if entering the scene
                    gameScene.Run();
                }; break;
                default: break;
            }
        } EndDrawing();
    }

    // Deinit game window
    CloseWindow();
    CloseAudioDevice();
}