#include "TitleScene.h"
#include "RenderUtilities.h"
#include "Button.h"
#include "Game.h"
#include "Scene.h"
#include "Properties.h"
#include "raylib.h"
#include "SaveLoadUtilities.h"
#include <string>

TitleScene titleScene;

// Init
void TitleScene::Init() {
    title = MAIN;    
}
void TitleScene::InitButtons() {
    // Duplicated buttons
    backButton.SetRatio(0, 10, 1, -70, 0, 180, 0, 60, BLANK,  {255, 255, 255, 100}); 
    backButton.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    backButton.SetSound(Properties::sounds["buttonClick"]);

    backLoadSaveButton.SetRatio(0.5, -90, 1, -70, 0, 180, 0, 60, BLANK,  {255, 255, 255, 100}); 
    backLoadSaveButton.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    backLoadSaveButton.SetSound(Properties::sounds["buttonClick"]);
    
    backModeButton.SetRatio(0.5, -130, 0.75, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    backModeButton.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    backModeButton.SetSound(Properties::sounds["buttonClick"]);

    // mainTitle
    newGameButton.SetRatio(0.5, -130, 0.5, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    newGameButton.SetText("New Game", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    newGameButton.SetSound(Properties::sounds["buttonClick"]);
    
    loadButton.SetRatio(0.5, -130, 5.0 / 8.0, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    loadButton.SetText("Load", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    loadButton.SetSound(Properties::sounds["buttonClick"]);
    
    optionsButton.SetRatio(0.5, -130, 0.75, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    optionsButton.SetText("Options", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    optionsButton.SetSound(Properties::sounds["buttonClick"]);
    
    exitButton.SetRatio(0.5, -130, 7.0 / 8.0, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    exitButton.SetText("Exit", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    exitButton.SetSound(Properties::sounds["buttonClick"]);
    
    // modeTitle
    onePlayerButton.SetRatio(0.5, -130, 0.5, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    onePlayerButton.SetText("1 Player", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    onePlayerButton.SetSound(Properties::sounds["buttonClick"]);
    
    twoPlayerButton.SetRatio(0.5, -130, 5.0 / 8.0, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    twoPlayerButton.SetText("2 Player", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    twoPlayerButton.SetSound(Properties::sounds["buttonClick"]);

    // onePlayerTitle
    chooseWhiteButton.SetRatio(0.5, -130, 0.5, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    chooseWhiteButton.SetText("White", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    chooseWhiteButton.SetSound(Properties::sounds["buttonClick"]);
    
    chooseBlackButton.SetRatio(0.5, -130, 5.0 / 8.0, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    chooseBlackButton.SetText("Black", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    chooseBlackButton.SetSound(Properties::sounds["buttonClick"]);

    // difficultyTitle
    easyDiffButton.SetRatio(0.5, -130, 0.5, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    easyDiffButton.SetText("Easy", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    easyDiffButton.SetSound(Properties::sounds["buttonClick"]);
    
    mediumDiffButton.SetRatio(0.5, -130, 5.0 / 8.0, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    mediumDiffButton.SetText("Medium", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    mediumDiffButton.SetSound(Properties::sounds["buttonClick"]);
    
    hardDiffButton.SetRatio(0.5, -130, 0.75, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    hardDiffButton.SetText("Hard", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    hardDiffButton.SetSound(Properties::sounds["buttonClick"]);

    backDiffButton.SetRatio(0.5, -130, 7.0 / 8.0, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
    backDiffButton.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    backDiffButton.SetSound(Properties::sounds["buttonClick"]);

    // loadTitle
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

void TitleScene::Run() {
    ClearBackground(RAYWHITE);
    switch(title) {
        case MAIN: {
            MainTitle();
        }; break;
        case MODE: {
            ModeTitle();
        }; break;
        case ONEPLAYER: {
            OnePlayerTitle();
        }; break;
        case DIFFICULTY: {
            DifficultyTitle();
        }; break;
        case LOAD: {
            LoadTitle();
        }; break;
        case OPTIONS: {
            OptionsTitle();
        }; break;
        default: break;
    }
}


void TitleScene::MainTitle() {
    // Render assets
    DrawTexturePro(Properties::elements["mainTitle"], (Rectangle) {0.0, 0.0, (float)Properties::elements["mainTitle"].width, (float)Properties::elements["mainTitle"].height}, 
                    Rectangle{0.0, 0.0, (float)GetScreenWidth(), (float)GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawTextCenEx(Properties::fonts["Mondwild_80"], "GAY CHESS", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);    

    // Render the buttons
    newGameButton.Render();
    loadButton.Render();
    optionsButton.Render();
    exitButton.Render();

    // Button detectings
    if (newGameButton.Check()) {
        title = MODE;
    }
    if (loadButton.Check()) {
        title = LOAD;
    }
    if (optionsButton.Check()) {
        title = OPTIONS;
    }
    if (exitButton.Check()) {
        Scene::ChangeScene(Scene::EXIT);
    }
}

void TitleScene::ModeTitle() {
    // Render assets
    DrawTexturePro(Properties::elements["mainTitle"], (Rectangle) {0.0, 0.0, (float) Properties::elements["mainTitle"].width, (float) Properties::elements["mainTitle"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawTextCenEx(Properties::fonts["Mondwild_80"], "Choose game mode", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);    

    // Render buttons
    onePlayerButton.Render();
    twoPlayerButton.Render();
    backModeButton.Render();

    // Button detectings
    if (onePlayerButton.Check()) {  
        game.Init();
        title = ONEPLAYER;
    }
    if (twoPlayerButton.Check()) {
        game.Init();
        Scene::ChangeScene(Scene::GAME_SCENE);
    }
    if(backModeButton.Check()) {
        title = MAIN;
    }
}

void TitleScene::DifficultyTitle() {
    // Render assets
    DrawTexturePro(Properties::elements["mainTitle"], (Rectangle) {0.0, 0.0, (float) Properties::elements["mainTitle"].width, (float) Properties::elements["mainTitle"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawTextCenEx(Properties::fonts["Mondwild_80"], "Choose difficulty", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);    
    
    // Render buttons
    easyDiffButton.Render();
    mediumDiffButton.Render();
    hardDiffButton.Render();
    backDiffButton.Render();

    CHESS_COLOR color = isWhite ? CHESS_BLACK : CHESS_WHITE;

    // Button detectings
    if (easyDiffButton.Check()) {  
        game.SetAgent(color, "Easy");
        Scene::ChangeScene(Scene::GAME_SCENE);
    }
    if (mediumDiffButton.Check()) {
        game.SetAgent(color, "Medium");
        Scene::ChangeScene(Scene::GAME_SCENE);
    }
    if (hardDiffButton.Check()) {
        game.SetAgent(color, "Hard");
        Scene::ChangeScene(Scene::GAME_SCENE);
    }
    if(backDiffButton.Check()) {
        title = ONEPLAYER;
    }
}

void TitleScene::OnePlayerTitle() {
    // Render assets
    DrawTexturePro(Properties::elements["mainTitle"], (Rectangle) {0.0, 0.0, (float) Properties::elements["mainTitle"].width, (float) Properties::elements["mainTitle"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawTextCenEx(Properties::fonts["Mondwild_80"], "Choose your side", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);    
    
    // Render buttons
    chooseWhiteButton.Render();
    chooseBlackButton.Render();
    backModeButton.Render();

    // Button detectings
    if (chooseWhiteButton.Check()) {  
        game.SetAgent(CHESS_WHITE, "Human");
        isWhite = true;
        title = DIFFICULTY;
    }
    if (chooseBlackButton.Check()) {
        game.SetAgent(CHESS_BLACK, "Human");
        isWhite = false;
        title = DIFFICULTY;
    }
    if(backModeButton.Check()) {
        title = MODE;
    }
}

void TitleScene::LoadTitle() {
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
        if(!SaveLoadUtilities::IsSlotEmpty(1)) {
            game.LoadGame(1);
            Scene::ChangeScene(Scene::GAME_SCENE);
        }
    }
    if(load2Button.Check()) {
        if(!SaveLoadUtilities::IsSlotEmpty(2)) {
            game.LoadGame(2);
            Scene::ChangeScene(Scene::GAME_SCENE);
        }
    }
    if(load3Button.Check()) {
        if(!SaveLoadUtilities::IsSlotEmpty(3)) {
            game.LoadGame(3);
            Scene::ChangeScene(Scene::GAME_SCENE);
        }
    }
    if (backLoadSaveButton.Check()) {
        title = MAIN;
    }
}

void TitleScene::OptionsTitle() {
    // Render assets
    DrawTexturePro(Properties::elements["optionsBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["optionsBackGround"].width, (float) Properties::elements["optionsBackGround"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawRectangle(Properties::GetBorderSize(), GetScreenHeight() / 6, GetScreenWidth() - 2 * Properties::GetBorderSize(), GetScreenHeight() * 5 / 6 - Properties::GetBorderSize(), Color{0, 0, 0, 100});
    DrawRectangle(GetScreenWidth() / 2 + Properties::GetBorderSize(), GetScreenHeight() / 6 + Properties::GetBorderSize(), GetScreenWidth() / 2 - 3 * Properties::GetBorderSize(), GetScreenHeight() * 5 / 6 - 3 * Properties::GetBorderSize(), Color{255, 255, 255, 100});
    DrawTextCenEx(Properties::fonts["Mondwild_80"], "Option", int(GetScreenWidth() / 2), int(GetScreenHeight() / 6), 80, 2, PINK);    
    
    // Render buttons
    backButton.Render();
    
    // Button detectings
    if (backButton.Check()) {
        title = MAIN;
    }
}