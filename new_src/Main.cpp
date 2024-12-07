#include "raylib.h"
#include "Properties.h"
#include "Scene.h"
#include "TitleScene.h"
#include "GameScene.h"

int main() {
    // Init game window
    InitWindow(Properties::screenWidth[1], Properties::screenHeight[1], "NEET Chess");
    InitAudioDevice();
    SetTargetFPS(60);
    SetExitKey(0);

    // Load assets
    Properties::LoadSounds();
    Properties::LoadMusics();
    Properties::LoadTextures();
    Properties::LoadElements();
    Properties::LoadFonts();

    // Variables initialization
    titleScene.InitButtons();
    gameScene.InitButtons();
    PlayMusicStream(Properties::musics["titleMusic"]);

    SetExitKey(0);

    // Main game loop
    while (!WindowShouldClose() && Scene::scene != Scene::EXIT) {
        Properties::UpdateMusics();
        Properties::ResetCursor();
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
            Properties::RenderCursor();
        } EndDrawing();
    }

    // Deinit game window
    CloseWindow();
    CloseAudioDevice();
}