#include "raylib.h"
#include "Properties.h"
#include "Game.h"

#include "bits/stdc++.h"

// Windows Info


int main() {
    // Init
    InitWindow(Properties::screenWidth, Properties::screenHeight, "CS160-chess-project");
    InitAudioDevice();

    // Setup

    // Insert all asserts
    Properties().LoadSounds();
    Properties().LoadTextures();

    Properties::currentScreen = LOGO;

    while(!WindowShouldClose()) {
        BeginDrawing(); {
            switch(Properties::currentScreen) {
                case LOGO: {
                    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                    {
                        Properties::currentScreen = TWOPLAYER;
                    }
                } break;
                case MAINMENU: {
                    // Enter main menu
                    // Menu::MainMenu();
                } break;
                case MODEMENU: {
                    // Enter mode menu
                    // Menu::Mode();
                } break;
                case ONEPLAYER: {
                    // Enter one player mode
                    //Game::OnePlayer();
                } break;
                case TWOPLAYER: {
                    // Enter two player mode
                    // Game::TwoPlayer();
                    Game().Run();
                } break;
                case WINLOSE: {
                    ClearBackground(RAYWHITE);
                    // Enter win/lose menu
                    // Menu::WinLose();
                } break;
                default: break;
            }
        } EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
}