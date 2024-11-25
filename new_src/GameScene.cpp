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
    Properties::isMusicPaused = false;
    Properties::ChangeMusic("gameMusic");
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
    newGameButton.SetHoveringText("New Game", 25, LIME, Properties::fonts["Rubik-Regular_25"]);
    newGameButton.SetSound(Properties::sounds["buttonClick"]);
    moveBackButton.SetHoveringText("Move back", 25, LIME, Properties::fonts["Rubik-Regular_25"]);
    moveBackButton.SetSound(Properties::sounds["buttonClick"]);
    moveForwardButton.SetHoveringText("Move forward", 25, LIME, Properties::fonts["Rubik-Regular_25"]);
    moveForwardButton.SetSound(Properties::sounds["buttonClick"]);
    settingsButton.SetHoveringText("Settings", 25, LIME, Properties::fonts["Rubik-Regular_25"]);
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
      
    exitButton.SetRatio(0.5, -130, 7.0 / 8.0, -35, 0, 260, 0, 70, BLANK,  {255, 255, 255, 100});
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

    muteMusicsButton.SetHoveringText("Music", 25, LIME, Properties::fonts["Rubik-Regular_25"]);
    muteMusicsButton.SetSound(Properties::sounds["buttonClick"]);
    muteSoundsButton.SetHoveringText("Sfx", 25, LIME, Properties::fonts["Rubik-Regular_25"]);
    muteSoundsButton.SetSound(Properties::sounds["buttonClick"]);
    
    leftButton.SetHoveringText("Previous theme", 25, LIME, Properties::fonts["Rubik-Regular_25"]);
    leftButton.SetSound(Properties::sounds["buttonClick"]);
    rightButton.SetHoveringText("Next theme", 25, LIME, Properties::fonts["Rubik-Regular_25"]);
    rightButton.SetSound(Properties::sounds["buttonClick"]);

    backOptionsButton.SetRatio(0.5, -90, 19.0 / 20.0, -30, 0, 180, 0, 60, BLANK,  {255, 255, 255, 100}); 
    backOptionsButton.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    backOptionsButton.SetSound(Properties::sounds["buttonClick"]);

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
    DrawRectangle(GetScreenHeight() + Properties::GetBorderSize(), Properties::GetBorderSize() * 2, GetScreenWidth() - GetScreenHeight() - 3 * Properties::GetBorderSize(), Properties::GetBorderSize() * 3, Color{255, 255, 255, 150});
    newGameButton.SetRec(Rectangle{(float) GetScreenHeight() + Properties::GetBorderSize(), (float) GetScreenHeight() - 2 * Properties::GetBorderSize() - 70,
        (float) GetScreenWidth() / 4 - GetScreenHeight() / 4 - Properties::GetBorderSize() * 3 / 4, 70},
            {200, 200, 200, 100}, {255, 255, 255, 100});
    newGameButton.SetTexture("newGame", "hoveringNewGame");
    moveBackButton.SetRec(Rectangle{(float) GetScreenHeight() + Properties::GetBorderSize() + 1 * (GetScreenWidth() / 4 - GetScreenHeight() / 4 - Properties::GetBorderSize() * 3 / 4), (float) GetScreenHeight() - 2 * Properties::GetBorderSize() - 70,
        (float) GetScreenWidth() / 4 - GetScreenHeight() / 4 - Properties::GetBorderSize() * 3 / 4, 70},
            {200, 200, 200, 100}, {255, 255, 255, 100});
    moveBackButton.SetTexture("moveBack", "hoveringMoveBack");
    moveForwardButton.SetRec(Rectangle{(float) GetScreenHeight() + Properties::GetBorderSize() + 2 * (GetScreenWidth() / 4 - GetScreenHeight() / 4 - Properties::GetBorderSize() * 3 / 4), (float) GetScreenHeight() - 2 * Properties::GetBorderSize() - 70,
        (float) GetScreenWidth() / 4 - GetScreenHeight() / 4 - Properties::GetBorderSize() * 3 / 4, 70},
            {200, 200, 200, 100}, {255, 255, 255, 100});
    moveForwardButton.SetTexture("moveForward", "hoveringMoveForward");
    settingsButton.SetRec(Rectangle{(float) GetScreenHeight() + Properties::GetBorderSize() + 3 * (GetScreenWidth() / 4 - GetScreenHeight() / 4 - Properties::GetBorderSize() * 3 / 4), (float) GetScreenHeight() - 2 * Properties::GetBorderSize() - 70,
        (float) GetScreenWidth() / 4 - GetScreenHeight() / 4 - Properties::GetBorderSize() * 3 / 4, 70},
            {200, 200, 200, 100}, {255, 255, 255, 100});
    settingsButton.SetTexture("settings", "hoveringSettings");

    // Text box
    if(game.GetVerdict() == CHESS_RUNNING) {
        std::string turnCount = "Turn: " + std::to_string(game.GetTurn());
        DrawTextRecEx(Properties::fonts["Rubik-Regular_45"], turnCount.c_str(), 
            Rectangle{(float) GetScreenHeight() + Properties::GetBorderSize(),(float) Properties::GetBorderSize() * 5 / 2,(float) GetScreenWidth() - GetScreenHeight() - 3 * Properties::GetBorderSize(),(float) Properties::GetBorderSize() * 1}, 45, 2, PINK);
        std::string currentTurn = "Current turn: ";
        
        if(game.GetTurn() % 2) {
            currentTurn += "Black";
        }
        else currentTurn += "White";
        DrawTextRecEx(Properties::fonts["Rubik-Regular_25"], currentTurn.c_str(), 
            Rectangle{(float) GetScreenHeight() + Properties::GetBorderSize(),(float) Properties::GetBorderSize() * 7 / 2,(float) GetScreenWidth() - GetScreenHeight() - 3 * Properties::GetBorderSize(),(float) Properties::GetBorderSize() * 1}, 25, 2, LIME);
    }

    // Scroll box for notations
    // ********Customable variable********
    // Define the scrollable text box area
    Rectangle textBox = {(float) GetScreenHeight() + Properties::GetBorderSize(),(float) Properties::GetBorderSize() * 6,
        (float) GetScreenWidth() - GetScreenHeight() - 3 * Properties::GetBorderSize(),(float) GetScreenHeight() - Properties::GetBorderSize() * 9 - 70};
    std::vector<std::string> notations;
    notations = game.GetNotations();
    int notationsSize = (notations.size() + 1) / 2;
    
    // Scrolling speed
    scrollOffSet -= GetMouseWheelMove() * 4;

    Color box = {200, 200, 200, 200}, bar = {80, 80, 80, 200};
    Color highlight = {255, 255, 255, 200};
    Font font = Properties::fonts["Rubik-Regular_25"];
    int fontSize = 25;
    int lineHeight = 30;
    // ***********************************

    // limit for better visual
    if(scrollOffSet > (int)notationsSize * lineHeight - (int)textBox.height) 
        scrollOffSet = (int)notationsSize * lineHeight - (int)textBox.height; // plus extra lineHeight to show the last line
    if(scrollOffSet < 0) scrollOffSet = 0;
    // Auto format when making moves
    if(game.GetTurn() != turn) {
        turn = game.GetTurn();
        scrollOffSet = (int)notationsSize * lineHeight - (int)textBox.height;
        if(scrollOffSet < 0) scrollOffSet = 0;
    }

    DrawRectangleRec(textBox, box);
    DrawRectangleLinesEx(textBox, 1, bar);

    int linesInView = (int)textBox.height / lineHeight;
    int firstLine = scrollOffSet / lineHeight;
    
    // Draw scroll bar
    float scrollbarHeight;
    if(notationsSize != 0) scrollbarHeight = textBox.height * ((float)linesInView / (float)notationsSize < 1 ? (float)linesInView / (float)notationsSize : 1);
    else scrollbarHeight = textBox.height;
    float scrollbarY;
    if(notationsSize != 0) scrollbarY = textBox.y + ((float)scrollOffSet / (notationsSize * lineHeight)) * textBox.height;
    else scrollbarY = textBox.y;
    
    DrawRectangle(textBox.x + textBox.width - 10, textBox.y, 10, textBox.height, box);
    DrawRectangle(textBox.x + textBox.width - 10, scrollbarY, 10, scrollbarHeight, bar);

    // start a local painting in textBox
    BeginScissorMode(textBox.x, textBox.y, textBox.width, textBox.height);
    for (int i = 0; i <= linesInView * 2 && firstLine * 2 + i < notations.size(); i += 2) {
        float yPos = textBox.y + (i / 2) * lineHeight - (scrollOffSet % lineHeight);
        if(firstLine * 2 + i == game.GetTurn() - 1) {
            DrawRectangle(textBox.x, yPos, textBox.width / 2 - 5, lineHeight, highlight);
            DrawRectangleLinesEx(Rectangle{textBox.x, yPos, textBox.width / 2 - 5,(float) lineHeight}, 1, bar);
        }
        DrawTextEx(font, notations[firstLine * 2 + i].c_str(), {textBox.x + 5, yPos}, fontSize, 2, BLACK);
        if(firstLine * 2 + i + 1 < notations.size()) {
            if(firstLine * 2 + i + 1 == game.GetTurn() - 1) {
                DrawRectangle(textBox.x + textBox.width / 2 - 5, yPos, textBox.width / 2 - 10, lineHeight, highlight);
                DrawRectangleLinesEx(Rectangle{textBox.x + textBox.width / 2 - 5, yPos, textBox.width / 2 - 5,(float) lineHeight}, 1, bar);
            }
            DrawTextEx(font, notations[firstLine * 2 + i + 1].c_str(), {textBox.x + 5 + textBox.width / 2, yPos}, fontSize, 2, BLACK);
        }
    }
    EndScissorMode();

    // chess game
    game.Render();

    // Render buttons
    settingsButton.Render();
    moveForwardButton.Render();
    moveBackButton.Render();
    newGameButton.Render();
}

void GameScene::MainGame() {
    BaseGame();

    // chess game
    game.Run();

    if(game.IsGameEnded()) {
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
    if(settingsButton.Check() || IsKeyPressed(KEY_ESCAPE)) {
        SetMouseCursor(0);
        Properties::ChangeMusicBegin("pauseMusic");
        state = PAUSE;
    }
}

void GameScene::PauseGame() {
    BaseGame();

    // Render the pause menu
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), {0, 0, 0, 200});

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
        Properties::ChangeMusicEnd("gameMusic");
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

    // updating state
    musicsVolume.SetProgressRatio(Properties::musicsVolume);
    soundsVolume.SetProgressRatio(Properties::soundsVolume);

    if(leftButton.Check()) {
        Properties::skin = (Properties::skin - 1 + 3) % 3;
        Properties::changeSkin(Properties::skin);
    }
    if(rightButton.Check()) {
        Properties::skin = (Properties::skin + 1) % 3;
        Properties::changeSkin(Properties::skin);
    }
    switch(Properties::skin) {
        case 0: {
            skin1Button.Render();

            DrawTexturePro(Properties::skin1["preview"], (Rectangle) {0.0, 0.0, (float) Properties::skin1["preview"].width, (float) Properties::skin1["preview"].height},
                (Rectangle) {(float) GetScreenWidth() / 2 + 2 * Properties::GetBorderSize(), (float) GetScreenHeight() / 2,
                    (float) GetScreenWidth() / 2 - 5 * Properties::GetBorderSize(), (float) (GetScreenWidth() / 2 - 5 * Properties::GetBorderSize()) * Properties::skin1["preview"].height / Properties::skin1["preview"].width}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        } break;
        case 1: {
            skin2Button.Render();

            DrawTexturePro(Properties::skin2["preview"], (Rectangle) {0.0, 0.0, (float) Properties::skin2["preview"].width, (float) Properties::skin2["preview"].height},
                (Rectangle) {(float) GetScreenWidth() / 2 + 2 * Properties::GetBorderSize(), (float) GetScreenHeight() / 2,
                    (float) GetScreenWidth() / 2 - 5 * Properties::GetBorderSize(), (float) (GetScreenWidth() / 2 - 5 * Properties::GetBorderSize()) * Properties::skin2["preview"].height / Properties::skin2["preview"].width}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        } break;
        case 2: {
            skin3Button.Render();

            DrawTexturePro(Properties::skin3["preview"], (Rectangle) {0.0, 0.0, (float) Properties::skin3["preview"].width, (float) Properties::skin3["preview"].height},
                (Rectangle) {(float) GetScreenWidth() / 2 + 2 * Properties::GetBorderSize(), (float) GetScreenHeight() / 2,
                    (float) GetScreenWidth() / 2 - 5 * Properties::GetBorderSize(), (float) (GetScreenWidth() / 2 - 5 * Properties::GetBorderSize()) * Properties::skin3["preview"].height / Properties::skin3["preview"].width}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        } break;
    }

    // Render buttons
    resolution1Button.Render();
    resolution2Button.Render();
    resolution3Button.Render();
    resolution4Button.Render();
    musicsVolume.Render();
    soundsVolume.Render();
    leftButton.Render();
    rightButton.Render();
    backOptionsButton.Render();
    muteMusicsButton.Render();
    muteSoundsButton.Render();

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

    std::string endCondition = "Turn: " + std::to_string(game.GetTurn());
    std::string currentTurn = "Game at turn: " + std::to_string(game.GetTurn());

    // End game state
    switch (game.GetVerdict()) {
        case WHITE_WINS: {
            endCondition = "WHITE WINS!";
        } break;
        case BLACK_WINS: {
            endCondition = "BLACK WINS!";
        } break;
        case STALEMENT: {
            endCondition = "STALEMATE!";
        } break;
        case INSUFFICIENT: {
            endCondition = "INSUFFICIENT MATERIAL!";
        } break;
        case FIFTYMOVE: {
            endCondition = "FIFTY MOVE RULE!";
        } break;
        case THREEFOLD: {
            endCondition = "THREEFOLD REPITITION!";
        } break;
    }

    DrawTextRecEx(Properties::fonts["Rubik-Regular_45"], endCondition.c_str(), 
        Rectangle{(float) GetScreenHeight() + Properties::GetBorderSize(),(float) Properties::GetBorderSize() * 5 / 2,(float) GetScreenWidth() - GetScreenHeight() - 3 * Properties::GetBorderSize(),(float) Properties::GetBorderSize() * 1}, 45, 2, PINK);
    DrawTextRecEx(Properties::fonts["Rubik-Regular_25"], currentTurn.c_str(), 
        Rectangle{(float) GetScreenHeight() + Properties::GetBorderSize(),(float) Properties::GetBorderSize() * 7 / 2,(float) GetScreenWidth() - GetScreenHeight() - 3 * Properties::GetBorderSize(),(float) Properties::GetBorderSize() * 1}, 25, 2, LIME);
    
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
    if(settingsButton.Check() || IsKeyPressed(KEY_ESCAPE)) {
        SetMouseCursor(0);
        Properties::ChangeMusicBegin("pauseMusic");
        state = PAUSE;
    }
}