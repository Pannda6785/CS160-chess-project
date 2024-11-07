#include "raylib.h"

#include "Scene.h"
#include "RenderUtilities.h"
#include "Properties.h"
#include "Button.h"
#include "Game.h"

class GameScene {
public:
    GameScene() {
        InitButtons();
        Init(); 
    }
    ~GameScene() {}

    void Init() {
        state = MAIN;
    }

    // Is called per frame. Controls the flow of the game scene.
    void Run() {
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

private:
    enum GAME_STATE {
        MAIN,
        PAUSE,
        SAVE,
        LOAD,
        OPTIONS,
        ENDED       
    }; 

    // Current mode game and scene
    GAME_STATE state;

    // List of buttons
    Button backButton;
    Button continueButton;
    Button saveButton;
    Button loadButton;
    Button optionsButton;

    void InitButtons() {
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
    }
    
    void MainGame() {
        // Background
        DrawLine(GetScreenHeight(), 0, GetScreenHeight(), GetScreenHeight(), BLACK);
        DrawTexturePro(Properties::elements["gameBackGround"], Rectangle{0, 0, (float)Properties::elements["gameBackGround"].width, (float)Properties::elements["gameBackGround"].height},
                       Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, Vector2{0, 0}, 0, WHITE);

        // Text box
        DrawText("This is the game, enjoy!", GetScreenHeight() + 30, 100, 25, RED);
        DrawText("Some information here for you nerds.", GetScreenHeight() + 30, 160, 15, LIGHTGRAY);

        game.Render();
        game.Run();

        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            SetMouseCursor(0);
            state = PAUSE;
        }

        backButton.Render();
        if(backButton.Check()) {
            Scene::ChangeScene(Scene::TITLE_SCENE);
        }
    }

    void PauseGame() {
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

    void SaveGame() {
        // Render assets
        DrawTexturePro(Properties::elements["saveBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, 
                       (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is save title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);

        backButton.Render();
        if (backButton.Check()) {
            state = PAUSE;
        }
    }

    void LoadGame() {
        // Render assets
        DrawTexturePro(Properties::elements["loadBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, 
                       (Rectangle) {0.0, 0.0, (float) GetScreenWidth(), (float) GetScreenHeight()}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is load title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);

        backButton.Render();
        if (backButton.Check()) {
            state = PAUSE;
        }
    }
    
    void OptionsGame() {
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
};