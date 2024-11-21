#include "raylib.h"
#include "Properties.h"
#include "Scene.h"
#include "TitleScene.h"
#include "GameScene.h"

int main() {
    // Init game window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // temporary disable
    InitWindow(Properties::screenWidth[1], Properties::screenHeight[1], "CS160-chess-project");
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

    // Main game loop
    while (!WindowShouldClose() && Scene::scene != Scene::EXIT) {
        Properties::UpdateMusics();
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