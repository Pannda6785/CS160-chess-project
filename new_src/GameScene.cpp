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
    backButton.SetRatio(0, 10, 1, -70, 0, 180, 0, 60, WHITE);
    backButton.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    backButton.SetSound(Properties::sounds["buttonClick"]);
    
    continueButton.SetRatio(0.5, -130, 3.0 / 8.0, -30, 0, 260, 0, 70, LIGHTGRAY);
    continueButton.SetText("Continue", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    continueButton.SetSound(Properties::sounds["buttonClick"]);
    
    saveButton.SetRatio(0.5, -130, 0.5, -30, 0, 260, 0, 70, LIGHTGRAY);
    saveButton.SetText("Save", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    saveButton.SetSound(Properties::sounds["buttonClick"]);
    
    loadButton.SetRatio(0.5, -130, 5.0 / 8.0, -30, 0, 260, 0, 70, LIGHTGRAY);
    loadButton.SetText("Load", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    loadButton.SetSound(Properties::sounds["buttonClick"]);
    
    optionsButton.SetRatio(0.5, -130, 0.75, -30, 0, 260, 0, 70, LIGHTGRAY);
    optionsButton.SetText("Options", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    optionsButton.SetSound(Properties::sounds["buttonClick"]);
    
    undoButton.SetRatio(0.75, -70, 0.6, -30, 0, 140, 0, 60, SKYBLUE);
    undoButton.SetText("Undo", 30, LIME, Properties::fonts["Rubik-Regular_45"]);
    undoButton.SetSound(Properties::sounds["buttonClick"]);
    
    redoButton.SetRatio(0.88, -70, 0.6, -30, 0, 140, 0, 60, SKYBLUE);
    redoButton.SetText("Redo", 30, LIME, Properties::fonts["Rubik-Regular_45"]);
    redoButton.SetSound(Properties::sounds["buttonClick"]);

    testLoadButton.SetRatio(0.75, -70, 0.7, -30, 0, 140, 0, 60, SKYBLUE);
    testLoadButton.SetText("Load", 30, LIME, Properties::fonts["Rubik-Regular_45"]);
    testLoadButton.SetSound(Properties::sounds["buttonClick"]);
    
    testSaveButton.SetRatio(0.88, -70, 0.7, -30, 0, 140, 0, 60, SKYBLUE);
    testSaveButton.SetText("Save", 30, LIME, Properties::fonts["Rubik-Regular_45"]);
    testSaveButton.SetSound(Properties::sounds["buttonClick"]);
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

    if (backButton.Check()) {
        Scene::ChangeScene(Scene::TITLE_SCENE);
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

    // Move to other scenes
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
}

void GameScene::SaveGame() {
    // Render assets
    DrawTexturePro(Properties::elements["saveBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is save title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);

    backButton.Render();
    if (backButton.Check()) {
        state = PAUSE;
    }
}

void GameScene::LoadGame() {
    // Render assets
    DrawTexturePro(Properties::elements["loadBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is load title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);

    backButton.Render();
    if (backButton.Check()) {
        state = PAUSE;
    }
}

void GameScene::OptionsGame() {
    // Render assets
    DrawTexturePro(Properties::elements["optionsBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    
    // Move to other scenes
    DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is option title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);
    
    backButton.Render();
    if (backButton.Check()) {
        state = PAUSE;
    }
}