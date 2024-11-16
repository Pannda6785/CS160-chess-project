#include "GameScene.h"
#include "RenderUtilities.h"
#include "Game.h"
#include "Properties.h"
#include "raylib.h"
#include "Scene.h"
#include "SaveLoadUtilities.h"

GameScene gameScene;

// INIT
void GameScene::Init() {
    state = MAIN;
}
void GameScene::InitButtons() {
    // Duplicated buttons
    backButton.SetRatio(0, 10, 1, -70, 0, 180, 0, 60, BLANK,  {255, 255, 255, 100});
    backButton.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    backButton.SetSound(Properties::sounds["buttonClick"]);

    backLoadSaveButton.SetRatio(0.5, -90, 1, -70, 0, 180, 0, 60, BLANK,  {255, 255, 255, 100}); 
    backLoadSaveButton.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    backLoadSaveButton.SetSound(Properties::sounds["buttonClick"]);

    // mainGame
    undoButton.SetRatio(0.75, -70, 0.6, -35, 0, 140, 0, 60, BLANK,  {255, 255, 255, 100});
    undoButton.SetText("Undo", 30, LIME, Properties::fonts["Rubik-Regular_45"]);
    undoButton.SetSound(Properties::sounds["buttonClick"]);
    
    redoButton.SetRatio(0.88, -70, 0.6, -35, 0, 140, 0, 60, BLANK,  {255, 255, 255, 100});
    redoButton.SetText("Redo", 30, LIME, Properties::fonts["Rubik-Regular_45"]);
    redoButton.SetSound(Properties::sounds["buttonClick"]);


    // pauseGame
    continueButton.SetRatio(0.5, -130, 3.0 / 8.0, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    continueButton.SetText("Continue", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    continueButton.SetSound(Properties::sounds["buttonClick"]);

    saveButton.SetRatio(0.5, -130, 0.5, -30, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    saveButton.SetText("Save", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    saveButton.SetSound(Properties::sounds["buttonClick"]);
    
    loadButton.SetRatio(0.5, -130, 5.0 / 8.0, -30, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    loadButton.SetText("Load", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    loadButton.SetSound(Properties::sounds["buttonClick"]);
    
    optionsButton.SetRatio(0.5, -130, 0.75, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    optionsButton.SetText("Options", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    optionsButton.SetSound(Properties::sounds["buttonClick"]);
      
    exitButton.SetRatio(0.5, -130, 7.0 / 8.0, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 0});
    exitButton.SetText("Exit", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    exitButton.SetSound(Properties::sounds["buttonClick"]);

    // saveGame
    save1Button.SetRatio(3.0 / 16.0, -130, 9.0 / 12.0, 0, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100}); 
    save1Button.SetText("Save", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    save1Button.SetSound(Properties::sounds["buttonClick"]);

    save2Button.SetRatio(8.0 / 16.0, -130, 5.0 / 6.0, 0, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100}); 
    save2Button.SetText("Save", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    save2Button.SetSound(Properties::sounds["buttonClick"]);

    save3Button.SetRatio(13.0 / 16.0, -130, 9.0 / 12.0, 0, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100}); 
    save3Button.SetText("Save", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    save3Button.SetSound(Properties::sounds["buttonClick"]);

    // loadGame
    load1Button.SetRatio(3.0 / 16.0, -130, 9.0 / 12.0, 0, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100}); 
    load1Button.SetText("Load", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    load1Button.SetSound(Properties::sounds["buttonClick"]);

    load2Button.SetRatio(8.0 / 16.0, -130, 5.0 / 6.0, 0, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100}); 
    load2Button.SetText("Load", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    load2Button.SetSound(Properties::sounds["buttonClick"]);

    load3Button.SetRatio(13.0 / 16.0, -130, 9.0 / 12.0, 0, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100}); 
    load3Button.SetText("Load", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    load3Button.SetSound(Properties::sounds["buttonClick"]);
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
    DrawTexturePro(Properties::skins["backGround"], Rectangle{0, 0, (float)Properties::skins["backGround"].width, (float)Properties::skins["backGround"].height},
                    Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, Vector2{0, 0}, 0, WHITE);

    // Text box
    DrawText("This is the game, enjoy!", GetScreenHeight() + 30, 100, 25, RED);
    DrawText("Some information here for you nerds.", GetScreenHeight() + 30, 160, 15, LIGHTGRAY);

    game.Render();
    game.Run();
    undoButton.Render();
    redoButton.Render();

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
    DrawTexturePro(Properties::elements["saveBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["saveBackGround"].width, (float) Properties::elements["saveBackGround"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawTextCenEx(Properties::fonts["Mondwild_80"], "Save", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);    
    
    // Save 1
    /*
    DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, 
                    (Rectangle) {(float) GetScreenWidth() * 1 / 16, (float) GetScreenHeight() / 2, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    */
    DrawRectangleRec((Rectangle) {(float) GetScreenWidth() * 1 / 16, (float) GetScreenHeight() * 5 / 12, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, {0, 0, 0, 100});
    if(!SaveLoadUtilities::IsSlotEmpty(1)) {
        std::string mode = "Mode: " + SaveLoadUtilities::GetMode(1);
        std::string played = "Played: " + SaveLoadUtilities::GetTurn(1) + " moves";
        std::string currentTurn = SaveLoadUtilities::GetWhoseTurn(1) + "'s turn";
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], mode.c_str(), 
            int(GetScreenWidth() * 1 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() * 5 / 12 + GetScreenHeight() / 3 * 1 / 4), 45, 2, PINK);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], played.c_str(), 
            int(GetScreenWidth() * 1 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() * 5 / 12 + GetScreenHeight() / 3 * 2 / 4), 45, 2, PINK);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], currentTurn.c_str(), 
            int(GetScreenWidth() * 1 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() * 5 / 12 + GetScreenHeight() / 3 * 3 / 4), 45, 2, PINK);
    }
    
    // Save 2
    /*
    DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, 
                    (Rectangle) {(float) GetScreenWidth() * 6 / 16, (float) GetScreenHeight() / 2, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    */
    DrawRectangleRec((Rectangle) {(float) GetScreenWidth() * 6 / 16, (float) GetScreenHeight() / 2, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, {0, 0, 0, 100});
    if(!SaveLoadUtilities::IsSlotEmpty(2)) {
        std::string mode = "Mode: " + SaveLoadUtilities::GetMode(2);
        std::string played = "Played: " + SaveLoadUtilities::GetTurn(2) + " moves";
        std::string currentTurn = SaveLoadUtilities::GetWhoseTurn(2) + "'s turn";
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], mode.c_str(), 
            int(GetScreenWidth() * 6 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() / 2 + GetScreenHeight() / 3 * 1 / 4), 45, 2, PINK);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], played.c_str(), 
            int(GetScreenWidth() * 6 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() / 2 + GetScreenHeight() / 3 * 2 / 4), 45, 2, PINK);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], currentTurn.c_str(), 
            int(GetScreenWidth() * 6 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() / 2 + GetScreenHeight() / 3 * 3 / 4), 45, 2, PINK);
    }

    // Save 3
    /*
    DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, 
                    (Rectangle) {(float) GetScreenWidth() * 11 / 16, (float) GetScreenHeight() / 2, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    */
    DrawRectangleRec((Rectangle) {(float) GetScreenWidth() * 11 / 16, (float) GetScreenHeight() * 5 / 12, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, {0, 0, 0, 100});
    if(!SaveLoadUtilities::IsSlotEmpty(3)) {
        std::string mode = "Mode: " + SaveLoadUtilities::GetMode(3);
        std::string played = "Played: " + SaveLoadUtilities::GetTurn(3) + " moves";
        std::string currentTurn = SaveLoadUtilities::GetWhoseTurn(3) + "'s turn";
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], mode.c_str(), 
            int(GetScreenWidth() * 11 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() * 5 / 12 + GetScreenHeight() / 3 * 1 / 4), 45, 2, PINK);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], played.c_str(), 
            int(GetScreenWidth() * 11 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() * 5 / 12 + GetScreenHeight() / 3 * 2 / 4), 45, 2, PINK);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], currentTurn.c_str(), 
            int(GetScreenWidth() * 11 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() * 5 / 12 + GetScreenHeight() / 3 * 3 / 4), 45, 2, PINK);
    }
    
    // Render buttons
    save1Button.Render();
    save2Button.Render();
    save3Button.Render();
    backLoadSaveButton.Render();

    // Button detectings
    if (save1Button.Check()) {
        game.SaveGame(1);
    }
    if(save2Button.Check()) {
        game.SaveGame(2);
    }
    if(save3Button.Check()) {
        game.SaveGame(3);
    }
    if (backLoadSaveButton.Check()) {
        state = PAUSE;
    }
}

void GameScene::LoadGame() {
    // Render assets
    DrawTexturePro(Properties::elements["loadBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["loadBackGround"].width, (float) Properties::elements["loadBackGround"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawTextCenEx(Properties::fonts["Mondwild_80"], "Load", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);    
    
    // Save 1
    /*
    DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, 
                    (Rectangle) {(float) GetScreenWidth() * 1 / 16, (float) GetScreenHeight() / 2, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    */
    DrawRectangleRec((Rectangle) {(float) GetScreenWidth() * 1 / 16, (float) GetScreenHeight() * 5 / 12, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, {0, 0, 0, 100});
    if(!SaveLoadUtilities::IsSlotEmpty(1)) {
        std::string mode = "Mode: " + SaveLoadUtilities::GetMode(1);
        std::string played = "Played: " + SaveLoadUtilities::GetTurn(1) + " moves";
        std::string currentTurn = SaveLoadUtilities::GetWhoseTurn(1) + "'s turn";
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], mode.c_str(), 
            int(GetScreenWidth() * 1 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() * 5 / 12 + GetScreenHeight() / 3 * 1 / 4), 45, 2, PINK);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], played.c_str(), 
            int(GetScreenWidth() * 1 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() * 5 / 12 + GetScreenHeight() / 3 * 2 / 4), 45, 2, PINK);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], currentTurn.c_str(), 
            int(GetScreenWidth() * 1 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() * 5 / 12 + GetScreenHeight() / 3 * 3 / 4), 45, 2, PINK);
    }
    
    // Save 2
    /*
    DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, 
                    (Rectangle) {(float) GetScreenWidth() * 6 / 16, (float) GetScreenHeight() / 2, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    */
    DrawRectangleRec((Rectangle) {(float) GetScreenWidth() * 6 / 16, (float) GetScreenHeight() / 2, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, {0, 0, 0, 100});
    if(!SaveLoadUtilities::IsSlotEmpty(2)) {
        std::string mode = "Mode: " + SaveLoadUtilities::GetMode(2);
        std::string played = "Played: " + SaveLoadUtilities::GetTurn(2) + " moves";
        std::string currentTurn = SaveLoadUtilities::GetWhoseTurn(2) + "'s turn";
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], mode.c_str(), 
            int(GetScreenWidth() * 6 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() / 2 + GetScreenHeight() / 3 * 1 / 4), 45, 2, PINK);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], played.c_str(), 
            int(GetScreenWidth() * 6 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() / 2 + GetScreenHeight() / 3 * 2 / 4), 45, 2, PINK);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], currentTurn.c_str(), 
            int(GetScreenWidth() * 6 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() / 2 + GetScreenHeight() / 3 * 3 / 4), 45, 2, PINK);
    }

    // Save 3
    /*
    DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, 
                    (Rectangle) {(float) GetScreenWidth() * 11 / 16, (float) GetScreenHeight() / 2, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    */
    DrawRectangleRec((Rectangle) {(float) GetScreenWidth() * 11 / 16, (float) GetScreenHeight() * 5 / 12, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, {0, 0, 0, 100});
    if(!SaveLoadUtilities::IsSlotEmpty(3)) {
        std::string mode = "Mode: " + SaveLoadUtilities::GetMode(3);
        std::string played = "Played: " + SaveLoadUtilities::GetTurn(3) + " moves";
        std::string currentTurn = SaveLoadUtilities::GetWhoseTurn(3) + "'s turn";
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], mode.c_str(), 
            int(GetScreenWidth() * 11 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() * 5 / 12 + GetScreenHeight() / 3 * 1 / 4), 45, 2, PINK);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], played.c_str(), 
            int(GetScreenWidth() * 11 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() * 5 / 12 + GetScreenHeight() / 3 * 2 / 4), 45, 2, PINK);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], currentTurn.c_str(), 
            int(GetScreenWidth() * 11 / 16 + GetScreenWidth() / 4 / 2), int(GetScreenHeight() * 5 / 12 + GetScreenHeight() / 3 * 3 / 4), 45, 2, PINK);
    }

    // Render buttons
    load1Button.Render();
    load2Button.Render();
    load3Button.Render();
    backLoadSaveButton.Render();

    // Button detectings
    if(load1Button.Check()) {
        game.LoadGame(1);
        state = MAIN;
    }
    if(load2Button.Check()) {
        game.LoadGame(2);
        state = MAIN;
    }
    if(load3Button.Check()) {
        game.LoadGame(3);
        state = MAIN;
    }
    if (backLoadSaveButton.Check()) {
        state = MAIN;
    }
}

void GameScene::OptionsGame() {
    // Render assets
    DrawTexturePro(Properties::elements["optionsBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["optionsBackGround"].width, (float) Properties::elements["optionsBackGround"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawTextCenEx(Properties::fonts["Mondwild_80"], "Option", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);    

    // Render buttons
    backButton.Render();

    // Button detectings
    if (backButton.Check()) {
        state = PAUSE;
    }
}