#include "raylib.h"
#include "Properties.h"
#include "Scene.h"
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
    Scene::scene = Scene::TITLE_SCENE;
    Scene::isSceneChanged = true;
    TitleScene titleScene;
    GameScene gameScene;

    // Main game loop
    while (!WindowShouldClose() && Scene::scene != Scene::EXIT) {
        if (IsKeyPressed(KEY_SPACE)) Properties::ToggleFullscreen();
        BeginDrawing(); {
            switch(Scene::scene) {
                case Scene::TITLE_SCENE: {
                    if (Scene::isSceneChanged) titleScene.Init(), Scene::isSceneChanged = false; // init the scene if entering the scene
                    titleScene.Run();
                }; break;
                case Scene::GAME_SCENE: {
                    if (Scene::isSceneChanged) gameScene.Init(), Scene::isSceneChanged = false; // init the scene if entering the scene
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