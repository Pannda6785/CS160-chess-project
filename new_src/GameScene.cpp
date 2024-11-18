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
    newGameButton.SetSound(Properties::sounds["buttonClick"]);
    moveBackButton.SetSound(Properties::sounds["buttonClick"]);
    moveForwardButton.SetSound(Properties::sounds["buttonClick"]);
    settingsButton.SetSound(Properties::sounds["buttonClick"]);

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

    // optionTitle
    musicsVolume.SetSound(Properties::sounds["buttonClick"]);
    soundsVolume.SetSound(Properties::sounds["buttonClick"]);

    resolution1Button.SetText("1280x800", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    resolution1Button.SetSound(Properties::sounds["buttonClick"]);
    resolution2Button.SetText("1366x768", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    resolution2Button.SetSound(Properties::sounds["buttonClick"]);
    resolution3Button.SetText("1440x900", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    resolution3Button.SetSound(Properties::sounds["buttonClick"]);
    resolution4Button.SetText("Fullscreen", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    resolution4Button.SetSound(Properties::sounds["buttonClick"]);

    skin1Button.SetText("Theme 1", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    skin1Button.SetSound(Properties::sounds["buttonClick"]);
    skin2Button.SetText("Theme 2", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    skin2Button.SetSound(Properties::sounds["buttonClick"]);
    skin3Button.SetText("Theme 3", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    skin3Button.SetSound(Properties::sounds["buttonClick"]);

    muteMusicsButton.SetSound(Properties::sounds["buttonClick"]);
    muteSoundsButton.SetSound(Properties::sounds["buttonClick"]);
    
    leftButton.SetSound(Properties::sounds["buttonClick"]);
    rightButton.SetSound(Properties::sounds["buttonClick"]);

    backOptionsButton.SetRatio(0.5, -90, 19.0 / 20.0, -30, 0, 180, 0, 60, BLANK,  {255, 255, 255, 100}); 
    backOptionsButton.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    backOptionsButton.SetSound(Properties::sounds["buttonClick"]);
}

// Is called per frame. Controls the flow of the game scene.
void GameScene::Run() {
    ClearBackground(RAYWHITE);
    switch(state) {
        case MAIN: {
            MainGame();
        } break;
        case PAUSE: {
            PauseGame();
        } break;
        case SAVE: {
            SaveGame();
        } break;
        case LOAD: {
            LoadGame();
        } break;
        case OPTIONS: {
            OptionsGame();
        } break;
        case ENDED: {
            EndGame();
        } break;
        default: break;
    }
}

void GameScene::BaseGame() {
    // Background
    DrawTexturePro(Properties::skins["backGround"], Rectangle{0, 0, (float)Properties::skins["backGround"].width, (float)Properties::skins["backGround"].height},
                    Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, Vector2{0, 0}, 0, WHITE);

    // Side panel
    DrawRectangle(GetScreenHeight(), Properties::GetBorderSize(), GetScreenWidth() - GetScreenHeight() - Properties::GetBorderSize(), GetScreenHeight() - Properties::GetBorderSize() * 2, Color{0, 0, 0, 100});
    newGameButton.SetRec(Rectangle{(float) GetScreenHeight() + Properties::GetBorderSize(), (float) GetScreenHeight() - 2 * Properties::GetBorderSize() - 70,
        (float) GetScreenWidth() / 4 - GetScreenHeight() / 4 - Properties::GetBorderSize() * 3 / 4, 70},
            {0, 158, 47, 100}, {255, 255, 255, 100});
    newGameButton.SetTexture("newGame", "hoveringNewGame");
    moveBackButton.SetRec(Rectangle{(float) GetScreenHeight() + Properties::GetBorderSize() + 1 * (GetScreenWidth() / 4 - GetScreenHeight() / 4 - Properties::GetBorderSize() * 3 / 4), (float) GetScreenHeight() - 2 * Properties::GetBorderSize() - 70,
        (float) GetScreenWidth() / 4 - GetScreenHeight() / 4 - Properties::GetBorderSize() * 3 / 4, 70},
            {0, 158, 47, 100}, {255, 255, 255, 100});
    moveBackButton.SetTexture("moveBack", "hoveringMoveBack");
    moveForwardButton.SetRec(Rectangle{(float) GetScreenHeight() + Properties::GetBorderSize() + 2 * (GetScreenWidth() / 4 - GetScreenHeight() / 4 - Properties::GetBorderSize() * 3 / 4), (float) GetScreenHeight() - 2 * Properties::GetBorderSize() - 70,
        (float) GetScreenWidth() / 4 - GetScreenHeight() / 4 - Properties::GetBorderSize() * 3 / 4, 70},
            {0, 158, 47, 100}, {255, 255, 255, 100});
    moveForwardButton.SetTexture("moveForward", "hoveringMoveForward");
    settingsButton.SetRec(Rectangle{(float) GetScreenHeight() + Properties::GetBorderSize() + 3 * (GetScreenWidth() / 4 - GetScreenHeight() / 4 - Properties::GetBorderSize() * 3 / 4), (float) GetScreenHeight() - 2 * Properties::GetBorderSize() - 70,
        (float) GetScreenWidth() / 4 - GetScreenHeight() / 4 - Properties::GetBorderSize() * 3 / 4, 70},
            {0, 158, 47, 100}, {255, 255, 255, 100});
    settingsButton.SetTexture("settings", "hoveringSettings");

    // Text box
    DrawText("This is the game, enjoy!", GetScreenHeight() + 30, 100, 25, RED);
    DrawText("Some information here for you nerds.", GetScreenHeight() + 30, 160, 15, LIGHTGRAY);

    // chess game
    game.Render();

    // Render buttons
    newGameButton.Render();
    moveBackButton.Render();
    moveForwardButton.Render();
    settingsButton.Render();
}

void GameScene::MainGame() {
    BaseGame();

    // chess game
    game.Run();

    if(game.IsGameEnded()) {
        PlaySound(Properties::sounds["buttonClick"]);
        state = ENDED;
    }
    if(newGameButton.Check()) {
        game.Init();
    }
    if(moveBackButton.Check()) {
        game.Undo();
    }
    if(moveForwardButton.Check()) {
        game.Redo();
    }
    if(settingsButton.Check()) {
        SetMouseCursor(0);
        Properties::ChangeMusic("pauseMusic");
        state = PAUSE;
    }
}

void GameScene::PauseGame() {
    BaseGame();

    // Render the pause menu
    DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is pause title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);
    
    // Render buttons
    continueButton.Render();
    saveButton.Render();
    loadButton.Render();
    optionsButton.Render();
    exitButton.Render();

    // End game
    if(game.IsGameEnded()) {
        switch (game.GetVerdict()) {
            case WHITE_WINS: {

            } break;
            case BLACK_WINS: {

            } break;
            case STALEMENT: {

            } break;
        }
    }

    // Button detectings
    if (continueButton.Check()) {
        Properties::ChangeMusic("gameMusic");
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
        Properties::ChangeMusic("titleMusic");
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
    DrawRectangle(Properties::GetBorderSize(), GetScreenHeight() / 6, GetScreenWidth() - 2 * Properties::GetBorderSize(), GetScreenHeight() * 5 / 6 - Properties::GetBorderSize(), Color{0, 0, 0, 100});
    DrawRectangle(GetScreenWidth() / 2 + Properties::GetBorderSize(), GetScreenHeight() / 6 + Properties::GetBorderSize(), GetScreenWidth() / 2 - 3 * Properties::GetBorderSize(), GetScreenHeight() * 5 / 6 - 3 * Properties::GetBorderSize(), Color{255, 255, 255, 100});
    DrawRectangle(Properties::GetBorderSize() * 2, GetScreenHeight() / 6 + Properties::GetBorderSize(), GetScreenWidth() / 2 - 3 * Properties::GetBorderSize(), GetScreenHeight() * 5 / 6 - 3 * Properties::GetBorderSize(), Color{255, 255, 255, 100});
    
    // Text
    DrawTextCenEx(Properties::fonts["Mondwild_80"], "Option", int(GetScreenWidth() / 2), int(GetScreenHeight() / 6), 80, 2, PINK);    
    DrawTextCenEx(Properties::fonts["Mondwild_45"], "Resolution", int(Properties::GetBorderSize() / 2 + GetScreenWidth() / 4), int(GetScreenHeight() / 6 + 2 * Properties::GetBorderSize()), 45, 2, PINK);    
    DrawTextCenEx(Properties::fonts["Mondwild_45"], "Chess themes", int(GetScreenWidth() * 3 / 4 - Properties::GetBorderSize() / 2), int(GetScreenHeight() / 6 + 2 * Properties::GetBorderSize()), 45, 2, PINK);    

    // Resize slider and button
    // TODO: change to screen ratio
    resolution1Button.SetRec(Rectangle{(float) Properties::GetBorderSize() * 5 / 4 + GetScreenWidth() / 8 - 100, (float) GetScreenHeight() / 6 + 3 * Properties::GetBorderSize(),(float) 200, 70},
                        BLANK, {255, 255, 255, 100});
    resolution2Button.SetRec(Rectangle{(float) GetScreenWidth() * 3 / 8 - Properties::GetBorderSize() / 4 - 100, (float) GetScreenHeight() / 6 + 3 * Properties::GetBorderSize(),(float) 200, 70},
                        BLANK, {255, 255, 255, 100});
    resolution3Button.SetRec(Rectangle{(float) Properties::GetBorderSize() * 5 / 4 + GetScreenWidth() / 8 - 100, (float) GetScreenHeight() / 6 + 3 * Properties::GetBorderSize() + 75,(float) 200, 70},
                        BLANK, {255, 255, 255, 100});
    resolution4Button.SetRec(Rectangle{(float) GetScreenWidth() * 3 / 8 - Properties::GetBorderSize() / 4 - 100, (float) GetScreenHeight() / 6 + 3 * Properties::GetBorderSize() + 75,(float) 200, 70},
                        BLANK, {255, 255, 255, 100});
    muteMusicsButton.SetRec(Rectangle{(float) Properties::GetBorderSize() * 4 - 35, (float) GetScreenHeight() * 5 / 8, 70, 70},
                        BLANK, {255, 255, 255, 100});
    if(!Properties::isMusicsMute) muteMusicsButton.SetTexture("musics", "hoveringMusics");
    else muteMusicsButton.SetTexture("muteMusics", "hoveringMuteMusics");
    musicsVolume.SetRec(Rectangle{(float) Properties::GetBorderSize() * 5, (float) GetScreenHeight() * 5 / 8,(float) GetScreenWidth() / 2 - 7 * Properties::GetBorderSize(), 70},
                        Color{0, 158, 47, 100}, Color{255, 109, 194, 255},  {255, 255, 255, 100});
    muteSoundsButton.SetRec(Rectangle{(float) Properties::GetBorderSize() * 4 - 35, (float) GetScreenHeight() * 6 / 8, 70, 70},
                        BLANK, {255, 255, 255, 100});
    if(Properties::isSoundsMute || Properties::soundsVolume == 0) muteSoundsButton.SetTexture("muteSounds", "hoveringMuteSounds");
    else if(Properties::soundsVolume < 0.4f) {
        muteSoundsButton.SetTexture("sounds1", "hoveringSounds1");
    }
    else if(Properties::soundsVolume < 0.7f) {
        muteSoundsButton.SetTexture("sounds2", "hoveringSounds2");
    }
    else muteSoundsButton.SetTexture("sounds3", "hoveringSounds3");
    soundsVolume.SetRec(Rectangle{(float) Properties::GetBorderSize() * 5, (float) GetScreenHeight() * 6 / 8,(float) GetScreenWidth() / 2 - 7 * Properties::GetBorderSize(), 70},
                        Color{0, 158, 47, 100}, Color{255, 109, 194, 255},  {255, 255, 255, 100});
    skin1Button.SetRec(Rectangle{(float) GetScreenWidth() * 3 / 4 - Properties::GetBorderSize() / 2 - 100, (float) GetScreenHeight() / 6 + 3 * Properties::GetBorderSize(),(float) 200, 70},
                        BLANK, {255, 255, 255, 100});
    skin2Button.SetRec(Rectangle{(float) GetScreenWidth() * 3 / 4 - Properties::GetBorderSize() / 2 - 100, (float) GetScreenHeight() / 6 + 3 * Properties::GetBorderSize(),(float) 200, 70},
                        BLANK, {255, 255, 255, 100});
    skin3Button.SetRec(Rectangle{(float) GetScreenWidth() * 3 / 4 - Properties::GetBorderSize() / 2 - 100, (float) GetScreenHeight() / 6 + 3 * Properties::GetBorderSize(),(float) 200, 70},
                        BLANK, {255, 255, 255, 100});
    leftButton.SetRec(Rectangle{(float) GetScreenWidth() * 3 / 4 - Properties::GetBorderSize() / 2 - 100 - 70, (float) GetScreenHeight() / 6 + 3 * Properties::GetBorderSize(),(float) 70, 70},
                        BLANK, {255, 255, 255, 100});
    leftButton.SetTexture("left", "hoveringLeft");
    rightButton.SetRec(Rectangle{(float) GetScreenWidth() * 3 / 4 - Properties::GetBorderSize() / 2 + 100, (float) GetScreenHeight() / 6 + 3 * Properties::GetBorderSize(),(float) 70, 70},
                        BLANK, {255, 255, 255, 100});
    rightButton.SetTexture("right", "hoveringRight");
    
    // Render buttons
    resolution1Button.Render();
    resolution2Button.Render();
    resolution3Button.Render();
    resolution4Button.Render();
    muteMusicsButton.Render();
    musicsVolume.Render();
    muteSoundsButton.Render();
    soundsVolume.Render();
    leftButton.Render();
    rightButton.Render();
    backOptionsButton.Render();

    // skin's skin
    if(leftButton.Check()) {
        Properties::skin = (Properties::skin - 1 + 3) % 3;
    }
    if(rightButton.Check()) {
        Properties::skin = (Properties::skin + 1) % 3;
    }
    switch(Properties::skin) {
        case 0: {
            skin1Button.Render();

            DrawTexturePro(Properties::skin1["preview"], (Rectangle) {0.0, 0.0, (float) Properties::skin1["preview"].width, (float) Properties::skin1["preview"].height},
                (Rectangle) {(float) GetScreenWidth() / 2 + 2 * Properties::GetBorderSize(), (float) GetScreenHeight() / 2,
                    (float) GetScreenWidth() / 2 - 5 * Properties::GetBorderSize(), (float) (GetScreenWidth() / 2 - 5 * Properties::GetBorderSize()) * Properties::skin1["preview"].height / Properties::skin1["preview"].width}, (Vector2) {0.0, 0.0}, 0.0, WHITE);

            if(skin1Button.Check()) {
                Properties::changeSkin(0);
            }
        } break;
        case 1: {
            skin2Button.Render();

            DrawTexturePro(Properties::skin2["preview"], (Rectangle) {0.0, 0.0, (float) Properties::skin2["preview"].width, (float) Properties::skin2["preview"].height},
                (Rectangle) {(float) GetScreenWidth() / 2 + 2 * Properties::GetBorderSize(), (float) GetScreenHeight() / 2,
                    (float) GetScreenWidth() / 2 - 5 * Properties::GetBorderSize(), (float) (GetScreenWidth() / 2 - 5 * Properties::GetBorderSize()) * Properties::skin2["preview"].height / Properties::skin2["preview"].width}, (Vector2) {0.0, 0.0}, 0.0, WHITE);


            if(skin2Button.Check()) {
                Properties::changeSkin(1);
            }
        } break;
        case 2: {
            skin3Button.Render();

            DrawTexturePro(Properties::skin3["preview"], (Rectangle) {0.0, 0.0, (float) Properties::skin3["preview"].width, (float) Properties::skin3["preview"].height},
                (Rectangle) {(float) GetScreenWidth() / 2 + 2 * Properties::GetBorderSize(), (float) GetScreenHeight() / 2,
                    (float) GetScreenWidth() / 2 - 5 * Properties::GetBorderSize(), (float) (GetScreenWidth() / 2 - 5 * Properties::GetBorderSize()) * Properties::skin3["preview"].height / Properties::skin3["preview"].width}, (Vector2) {0.0, 0.0}, 0.0, WHITE);

            if(skin3Button.Check()) {
                Properties::changeSkin(2);
            }
        } break;
    }

    // Button detectings
    if(resolution1Button.Check()) {
        Properties::ToggleFullscreen(0);
    }
    if(resolution2Button.Check()) {
        Properties::ToggleFullscreen(1);
    }
    if(resolution3Button.Check()) {
        Properties::ToggleFullscreen(2);
    }
    if(resolution4Button.Check()) {
        Properties::ToggleFullscreen(3);
    }
    if(muteMusicsButton.Check()) {
        Properties::MuteMusics();
    }
    if(musicsVolume.Check()) {
        Properties::SetMusicsVolume(musicsVolume.Get());
    }
    if(muteSoundsButton.Check()) {
        Properties::MuteSounds();
    }
    if(soundsVolume.Check()) {
        Properties::SetSoundsVolume(soundsVolume.Get());
    }
    if(backOptionsButton.Check()) {
        state = PAUSE;
    }
}

void GameScene::EndGame() {
    BaseGame();

    // End game state
    switch (game.GetVerdict()) {
        case WHITE_WINS: {
            DrawTextCenEx(Properties::fonts["Mondwild_80"], "White wins!", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);    
        } break;
        case BLACK_WINS: {
            DrawTextCenEx(Properties::fonts["Mondwild_80"], "Black wins!", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);     
        } break;
        case STALEMENT: {
            DrawTextCenEx(Properties::fonts["Mondwild_80"], "Stalemate!", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);    
        } break;
        case INSUFFICIENT: {
            DrawTextCenEx(Properties::fonts["Mondwild_80"], "Insufficient Material!", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);    
        } break;
        case FIFTYMOVE: {
            DrawTextCenEx(Properties::fonts["Mondwild_80"], "50 Move Rule!", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);     
        } break;
        case THREEFOLD: {
            DrawTextCenEx(Properties::fonts["Mondwild_80"], "Threefold Repetition!", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);     
        } break;
    }

    if(!game.IsGameEnded()) {
        state = MAIN;
    }
    if(newGameButton.Check()) {
        game.Init();
    }
    if(moveBackButton.Check()) {
        game.Undo();
    }
    if(moveForwardButton.Check()) {
        game.Redo();
    }
    if(settingsButton.Check()) {
        SetMouseCursor(0);
        Properties::ChangeMusic("pauseMusic");
        state = PAUSE;
    }
}