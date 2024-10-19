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

    scene = TITLESCENE;
    Title title;
    Game game;

     while(!WindowShouldClose()) {
        BeginDrawing(); {
            switch(scene) {
                case TITLESCENE: {
                    title.Run();
                }; break;
                case GAMESCENE: {
                    game.Run();
                }; break;
                default: break;
            }
        } EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
}