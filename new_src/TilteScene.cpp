#include "TitleScene.h"
#include "RenderUtilities.h"
#include "Button.h"
#include "Game.h"
#include "Scene.h"
#include "Properties.h"
#include "raylib.h"

TitleScene titleScene;

// Init
void TitleScene::Init() {
    title = MAIN;    
}
void TitleScene::InitButtons() {
    // Duplicated buttons
    backButton.SetRatio(0, 10, 1, -70, 0, 180, 0, 60, {255, 255, 255, 100}); 
    backButton.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    backButton.SetSound(Properties::sounds["buttonClick"]);

    backLoadSaveButton.SetRatio(0.5, -90, 1, -70, 0, 180, 0, 60, {255, 255, 255, 100}); 
    backLoadSaveButton.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    backLoadSaveButton.SetSound(Properties::sounds["buttonClick"]);
    
    // mainTitle
    newGameButton.SetRatio(0.5, -130, 0.5, -35, 0, 260, 0, 70, {255, 255, 255, 100});
    newGameButton.SetText("New Game", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    newGameButton.SetSound(Properties::sounds["buttonClick"]);
    
    loadButton.SetRatio(0.5, -130, 5.0 / 8.0, -35, 0, 260, 0, 70, {255, 255, 255, 100});
    loadButton.SetText("Load", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    loadButton.SetSound(Properties::sounds["buttonClick"]);
    
    optionsButton.SetRatio(0.5, -130, 0.75, -35, 0, 260, 0, 70, {255, 255, 255, 100});
    optionsButton.SetText("Options", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    optionsButton.SetSound(Properties::sounds["buttonClick"]);
    
    exitButton.SetRatio(0.5, -130, 7.0 / 8.0, -35, 0, 260, 0, 70, {255, 255, 255, 100});
    exitButton.SetText("Exit", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    exitButton.SetSound(Properties::sounds["buttonClick"]);
    
    // modeTitle
    onePlayerButton.SetRatio(0.5, -130, 0.5, -35, 0, 260, 0, 70, {255, 255, 255, 100});
    onePlayerButton.SetText("1 Player", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    onePlayerButton.SetSound(Properties::sounds["buttonClick"]);
    
    twoPlayerButton.SetRatio(0.5, -130, 5.0 / 8.0, -35, 0, 260, 0, 70, {255, 255, 255, 100});
    twoPlayerButton.SetText("2 Player", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    twoPlayerButton.SetSound(Properties::sounds["buttonClick"]);

    backModeButton.SetRatio(0.5, -130, 0.75, -35, 0, 260, 0, 70, {255, 255, 255, 100});
    backModeButton.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    backModeButton.SetSound(Properties::sounds["buttonClick"]);

    // difficultyTitle
    easyDiffButton.SetRatio(0.5, -130, 0.5, -35, 0, 260, 0, 70, {255, 255, 255, 100});
    easyDiffButton.SetText("Easy", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    easyDiffButton.SetSound(Properties::sounds["buttonClick"]);
    
    mediumDiffButton.SetRatio(0.5, -130, 5.0 / 8.0, -35, 0, 260, 0, 70, {255, 255, 255, 100});
    mediumDiffButton.SetText("Medium", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    mediumDiffButton.SetSound(Properties::sounds["buttonClick"]);
    
    hardDiffButton.SetRatio(0.5, -130, 0.75, -35, 0, 260, 0, 70, {255, 255, 255, 100});
    hardDiffButton.SetText("Hard", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    hardDiffButton.SetSound(Properties::sounds["buttonClick"]);

    backDiffButton.SetRatio(0.5, -130, 7.0 / 8.0, -35, 0, 260, 0, 70, {255, 255, 255, 100});
    backDiffButton.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    backDiffButton.SetSound(Properties::sounds["buttonClick"]);

    // saveTitle
    save1Button.SetRatio(3.0 / 16.0, -130, 1, -35, 0, 260, 0, 70, {255, 255, 255, 100}); 
    save1Button.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
    save1Button.SetSound(Properties::sounds["buttonClick"]);

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
    DrawTexturePro(Properties::elements["temp"], (Rectangle) {0.0, 0.0, (float)Properties::elements["temp"].width, (float)Properties::elements["temp"].height}, 
                    Rectangle{0.0, 0.0, (float)GetScreenWidth(), (float)GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    
    DrawTextCenEx(Properties::fonts["fontC_80"], "GAY CHESS", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);

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
    
    DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "GAY CHESS", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);

    // Render buttons
    onePlayerButton.Render();
    twoPlayerButton.Render();
    backModeButton.Render();

    // Button detectings
    if (onePlayerButton.Check()) {  
        game.Init();
        title = DIFFICULTY;
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
    
    DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "GAY CHESS", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);
    
    // Render buttons
    easyDiffButton.Render();
    mediumDiffButton.Render();
    hardDiffButton.Render();
    backDiffButton.Render();

    // Button detectings
    if (easyDiffButton.Check()) {  
        game.Init();
        Scene::ChangeScene(Scene::GAME_SCENE);
    }
    if (mediumDiffButton.Check()) {
        game.Init();
        Scene::ChangeScene(Scene::GAME_SCENE);
    }
    if (hardDiffButton.Check()) {
        game.Init();
        Scene::ChangeScene(Scene::GAME_SCENE);
    }
    if(backDiffButton.Check()) {
        title = MODE;
    }
}

void TitleScene::LoadTitle() {
    // Render assets
    DrawTexturePro(Properties::elements["loadBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["loadBackGround"].width, (float) Properties::elements["loadBackGround"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, 
                    (Rectangle) {(float) GetScreenWidth() * 1 / 16, (float) GetScreenHeight() / 2, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, 
                    (Rectangle) {(float) GetScreenWidth() * 6 / 16, (float) GetScreenHeight() / 2, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, 
                    (Rectangle) {(float) GetScreenWidth() * 11 / 16, (float) GetScreenHeight() / 2, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    
    DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is load title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);


    // Render buttons
    backLoadSaveButton.Render();

    // Button detectings
    if (backLoadSaveButton.Check()) {
        title = MAIN;
    }
}

void TitleScene::OptionsTitle() {
    // Render assets
    DrawTexturePro(Properties::elements["optionsBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, 
                    (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    
    DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is option title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);
    
    // Render buttons
    backButton.Render();
    
    // Button detectings
    if (backButton.Check()) {
        title = MAIN;
    }
}