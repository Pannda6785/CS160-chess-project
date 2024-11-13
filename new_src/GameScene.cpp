#include "GameScene.h"
#include "RenderUtilities.h"
#include "Game.h"
#include "Properties.h"
#include "raylib.h"
#include "Scene.h"

GameScene gameScene;

// INIT
void GameScene::Init() {
    state = MAIN;
}
void GameScene::InitButtons() {
    // Duplicated buttons
    backButton.SetRatio(0, 10, 1, -70, 0, 180, 0, 60, LIGHTGRAY, WHITE);
    backButton.SetText("Exit", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    backButton.SetSound(Properties::sounds["buttonClick"]);

    // pauseGame
    continueButton.SetRatio(0.5, -130, 3.0 / 8.0, -30, 0, 260, 0, 70, LIGHTGRAY, WHITE);
    continueButton.SetText("Continue", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    continueButton.SetSound(Properties::sounds["buttonClick"]);
    
    saveButton.SetRatio(0.5, -130, 0.5, -30, 0, 260, 0, 70, LIGHTGRAY, WHITE);
    saveButton.SetText("Save", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    saveButton.SetSound(Properties::sounds["buttonClick"]);
    
    loadButton.SetRatio(0.5, -130, 5.0 / 8.0, -30, 0, 260, 0, 70, LIGHTGRAY, WHITE);
    loadButton.SetText("Load", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    loadButton.SetSound(Properties::sounds["buttonClick"]);
    
    optionsButton.SetRatio(0.5, -130, 0.75, -30, 0, 260, 0, 70, LIGHTGRAY, WHITE);
    optionsButton.SetText("Options", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    optionsButton.SetSound(Properties::sounds["buttonClick"]);
    
    undoButton.SetRatio(0.75, -70, 0.6, -30, 0, 140, 0, 60, SKYBLUE, WHITE);
    undoButton.SetText("Undo", 30, LIME, Properties::fonts["Rubik-Regular_45"]);
    undoButton.SetSound(Properties::sounds["buttonClick"]);
    
    redoButton.SetRatio(0.88, -70, 0.6, -30, 0, 140, 0, 60, SKYBLUE, WHITE);
    redoButton.SetText("Redo", 30, LIME, Properties::fonts["Rubik-Regular_45"]);
    redoButton.SetSound(Properties::sounds["buttonClick"]);

    testLoadButton.SetRatio(0.75, -70, 0.7, -30, 0, 140, 0, 60, SKYBLUE, WHITE);
    testLoadButton.SetText("Load", 30, LIME, Properties::fonts["Rubik-Regular_45"]);
    testLoadButton.SetSound(Properties::sounds["buttonClick"]);
    
    testSaveButton.SetRatio(0.88, -70, 0.7, -30, 0, 140, 0, 60, SKYBLUE, WHITE);
    testSaveButton.SetText("Save", 30, LIME, Properties::fonts["Rubik-Regular_45"]);
    testSaveButton.SetSound(Properties::sounds["buttonClick"]);
  
    exitButton.SetRatio(0.5, -130, 7.0 / 8.0, -30, 0, 260, 0, 70, LIGHTGRAY, WHITE);
    exitButton.SetText("Exit", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    exitButton.SetSound(Properties::sounds["buttonClick"]);
}

// Is called per frame. Controls the flow of the game scene.
void GameScene::Run() {
    ClearBackground(RAYWHITE);
    switch(state) {
        case MAIN: {
            MainGame();
        }; break;
        case PAUSE: {
            PauseGame();
        }; break;
        case SAVE: {
            SaveGame();
        }; break;
        case LOAD: {
            LoadGame();
        }; break;
        case OPTIONS: {
            OptionsGame();
        }; break;
        default: break;
    }
}


void GameScene::MainGame() {
    // Background
    DrawLine(GetScreenHeight(), 0, GetScreenHeight(), GetScreenHeight(), BLACK);
    DrawTexturePro(Properties::elements["gameBackGround"], Rectangle{0, 0, (float)Properties::elements["gameBackGround"].width, (float)Properties::elements["gameBackGround"].height},
                    Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, Vector2{0, 0}, 0, WHITE);

    // Text box
    DrawText("This is the game, enjoy!", GetScreenHeight() + 30, 100, 25, RED);
    DrawText("Some information here for you nerds.", GetScreenHeight() + 30, 160, 15, LIGHTGRAY);

    game.Render();
    game.Run();
    undoButton.Render();
    redoButton.Render();
    backButton.Render();

    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        SetMouseCursor(0);
        state = PAUSE;
        return;
    }

    if (undoButton.Check()) {
        game.Undo();
    }
    if (redoButton.Check()) {
        game.Redo();
    }

    // TESTING
    testSaveButton.Render();
    testLoadButton.Render();
    if (testSaveButton.Check()) {
        game.SaveGame(1);
    }
    if (testLoadButton.Check()) {
        game.LoadGame(1); // please do not call when slot is empty
    }
}

void GameScene::PauseGame() {
    // Render the game in background and the overlaying tint. THIS IS THE SAME AS THAT IN MainGame()
    DrawLine(GetScreenHeight(), 0, GetScreenHeight(), GetScreenHeight(), BLACK);
    DrawTexturePro(Properties::elements["gameBackGround"], Rectangle{0, 0, (float)Properties::elements["gameBackGround"].width, (float)Properties::elements["gameBackGround"].height},
                    Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, Vector2{0, 0}, 0, WHITE);
    DrawText("This is the game, enjoy!", GetScreenHeight() + 30, 100, 25, RED);
    DrawText("Some information here for you nerds.", GetScreenHeight() + 30, 160, 15, LIGHTGRAY);
    game.Render();

    // Tinting the screen
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 150}); // Dark overlay
    
    // Render the pause menu
    DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is pause title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);
    
    // Render buttons
    continueButton.Render();
    saveButton.Render();
    loadButton.Render();
    optionsButton.Render();
    undoButton.Render();
    redoButton.Render();
    exitButton.Render();

    // Button detectings
    if (continueButton.Check()) {
        state = MAIN;
    }
    if (saveButton.Check()) {
        state = SAVE;
    }
    if (loadButton.Check()) {
        state = LOAD;
    }
    if (optionsButton.Check()) {
        state = OPTIONS;
    }
    if(exitButton.Check()) {
        Scene::ChangeScene(Scene::TITLE_SCENE);
    }
}

void GameScene::SaveGame() {
    // Render assets
    DrawTexturePro(Properties::elements["saveBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is save title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);
    // Render buttons
    backButton.Render();

    // Button detectings
    if (backButton.Check()) {
        state = PAUSE;
    }
}

void GameScene::LoadGame() {
    // Render assets
    DrawTexturePro(Properties::elements["loadBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is load title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);

    // Render buttons
    backButton.Render();

    // Button detectings
    if (backButton.Check()) {
        state = PAUSE;
    }
}

void GameScene::OptionsGame() {
    // Render assets
    DrawTexturePro(Properties::elements["optionsBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    
    DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is option title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);
    // Render buttons
    backButton.Render();

    // Button detectings
    if (backButton.Check()) {
        state = PAUSE;
    }
}