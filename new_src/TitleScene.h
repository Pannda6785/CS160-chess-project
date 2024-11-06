#include "raylib.h"
#include "vector"

#include "RenderUtilities.h"
#include "Properties.h"
#include "Button.h"
#include "Game.h"

class TitleScene {
public:
    TitleScene() { 
        InitButtons();
        Init(); 
    }
    ~TitleScene() {}

    void Init() {
        title = MAIN;    
    }

    // Is called per frame. Controls the flow of the title scene.
    void Run() {
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

private:
    enum TITLE {
        MAIN,
        MODE,
        DIFFICULTY,
        SAVE,
        LOAD,
        OPTIONS
    };

    // lists of pre-title for backButton
    TITLE title;

    // List of buttons 
    Button backButton;
    // Main title buttons
    Button newGameButton;
    Button loadButton;
    Button optionsButton;
    Button exitButton;
    // Mode title buttons
    Button onePlayerButton;
    Button twoPlayerButton;

    void InitButtons() {
        backButton.SetRatio(0, 10, 1, -70, 0, 180, 0, 60, WHITE); 
        backButton.SetText("Back", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
        backButton.SetSound(Properties::sounds["buttonClick"]);
        
        newGameButton.SetRatio(0.5, -130, 0.5, -30, 0, 260, 0, 70, LIGHTGRAY);
        newGameButton.SetText("New Game", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
        newGameButton.SetSound(Properties::sounds["buttonClick"]);
        
        loadButton.SetRatio(0.5, -130, 5.0 / 8.0, -30, 0, 260, 0, 70, LIGHTGRAY);
        loadButton.SetText("Load", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
        loadButton.SetSound(Properties::sounds["buttonClick"]);
        
        optionsButton.SetRatio(0.5, -130, 0.75, -30, 0, 260, 0, 70, LIGHTGRAY);
        optionsButton.SetText("Options", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
        optionsButton.SetSound(Properties::sounds["buttonClick"]);
        
        exitButton.SetRatio(0.5, -130, 7.0 / 8.0, -30, 0, 260, 0, 70, LIGHTGRAY);
        exitButton.SetText("Exit", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
        exitButton.SetSound(Properties::sounds["buttonClick"]);
        
        onePlayerButton.SetRatio(0.5, -130, 0.5, -30, 0, 260, 0, 70, LIGHTGRAY);
        onePlayerButton.SetText("1 Player", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
        onePlayerButton.SetSound(Properties::sounds["buttonClick"]);
        
        twoPlayerButton.SetRatio(0.5, -130, 5.0 / 8.0, -30, 0, 260, 0, 70, LIGHTGRAY);
        twoPlayerButton.SetText("2 Player", 45, LIME, Properties::fonts["Rubik-Regular_45"]);
        twoPlayerButton.SetSound(Properties::sounds["buttonClick"]);
    }
    
    void MainTitle() {
        // Render assets
        DrawTexturePro(Properties::elements["mainTitle"], (Rectangle) {0.0, 0.0, (float)Properties::elements["mainTitle"].width, (float)Properties::elements["mainTitle"].height}, 
                       Rectangle{0.0, 0.0, (float)GetScreenWidth(), (float)GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "GAY CHESS", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);

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
            ChangeScene(EXIT);
        }
    }

    void ModeTitle() {
        // Render assets
        DrawTexturePro(Properties::elements["mainTitle"], (Rectangle) {0.0, 0.0, (float) Properties::elements["mainTitle"].width, (float) Properties::elements["mainTitle"].height}, 
                       (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "GAY CHESS", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);

        // Render buttons
        onePlayerButton.Render();
        twoPlayerButton.Render();
        backButton.Render();

        // Button detectings
        if (onePlayerButton.Check()) {  
            game.Init();
            ChangeScene(GAME_SCENE);
        }
        if (twoPlayerButton.Check()) {
            game.Init();
            ChangeScene(GAME_SCENE);
        }
        if (backButton.Check()) {
            title = MAIN;
        }
    }

    void DifficultyTitle() {
        // Render assets
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is difficulty title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 4), 80, 2, PINK);
        
        backButton.Render();
        if (backButton.Check()) {
            title = MODE;
        }
    }

    void LoadTitle() {
        // Render assets
        DrawTexturePro(Properties::elements["loadBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["loadBackGround"].width, (float) Properties::elements["loadBackGround"].height}, 
                       (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, 
                       (Rectangle) {(float) GetScreenWidth() / 12, (float) GetScreenHeight() / 2, (float) GetScreenWidth() / 4, (float) GetScreenHeight() / 3}, (Vector2) {0.0, 0.0}, 0.0, WHITE);

        backButton.Render();
        if (backButton.Check()) {
            title = MAIN;
        }
    }

    void OptionsTitle() {
        // Render assets
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is option title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 4), 80, 2, PINK);
        
        backButton.Render();
        if (backButton.Check()) {
            title = MAIN;
        }
    }

};