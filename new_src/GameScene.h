#include "raylib.h"
#include "Properties.h"
#include "Button.h"
#include "RenderUtilities.h"
#include "game.h"

class GameScene {
public:
    GameScene() { Init(); }
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
    bool is1PLayer;

    // Repeated buttons. Need to define first
    Button backButton = Button(Rectangle{10, (float)GetScreenHeight() - 70, 180, 60}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Back", 45, LIME);

    void MainGame() {
        // Side panel
        // Background
        DrawLine(GetScreenHeight(), 0, GetScreenHeight(), GetScreenHeight(), BLACK);
        DrawTexturePro(Properties::elements["gameBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, (Rectangle) {0.0, 0.0, (float) Properties::screenWidth, (float) Properties::screenHeight}, (Vector2) {0.0, 0.0}, 0.0, WHITE);

        // Text box
        DrawText("This is the game, enjoy!", GetScreenHeight() + 30, 100, 25, RED);
        DrawText("Some information here for you nerds.", GetScreenHeight() + 30, 160, 15, LIGHTGRAY);

        game.Run();
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            state = PAUSE;
        }
        if(backButton.Check()) {
            ChangeScene(TITLE_SCENE);
        }
    }

    Button continueButton = Button(Rectangle{(float)GetScreenWidth() / 2 - 130, (float)GetScreenHeight() * 3 / 8 - 30, 260, 70}, LIGHTGRAY, Properties::textures[""], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Continue", 45, LIME);
    Button saveButton = Button(Rectangle{(float)GetScreenWidth() / 2 - 130, (float)GetScreenHeight() / 2 - 30, 260, 70}, LIGHTGRAY, Properties::textures[""], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Save", 45, LIME);
    Button loadButton = Button(Rectangle{(float)GetScreenWidth() / 2 - 130, (float)GetScreenHeight() * 5 / 8- 30, 260, 70}, LIGHTGRAY, Properties::textures[""], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Load", 45, LIME);
    Button optionsButton = Button(Rectangle{(float)GetScreenWidth() / 2 - 130, (float)GetScreenHeight() * 3 / 4 - 30, 260, 70}, LIGHTGRAY, Properties::textures[""], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Options", 45, LIME);
    void PauseGame() {
        // Render assets
        // Draw the tint over the background
        DrawRectangle(0, 0, Properties::screenWidth, Properties::screenHeight, (Color){0, 0, 0, 150}); // Dark overlay
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is pause title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);
        
        // Move to other scenes
        if(continueButton.Check()) {
            state = MAIN;
        }
        if(saveButton.Check()) {
            state = SAVE;
        }
        if(loadButton.Check()) {
            state = LOAD;
        }
        if(optionsButton.Check()) {
            state = OPTIONS;
        }
    }

    void SaveGame() {
        // Render assets
        DrawTexturePro(Properties::elements["saveBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, (Rectangle) {0.0, 0.0, (float) Properties::screenWidth, (float) Properties::screenHeight}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is save title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);

        // Move to other scenes
        if(backButton.Check()) {
            state = PAUSE;
        }
    }

    void LoadGame() {
        // Render assets
        DrawTexturePro(Properties::elements["loadBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, (Rectangle) {0.0, 0.0, (float) Properties::screenWidth, (float) Properties::screenHeight}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is load title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);

        // Move to other scenes
        if(backButton.Check()) {
            state = PAUSE;
        }
    }
    
    void OptionsGame() {
        // Render assets
        DrawTexturePro(Properties::elements["optionsBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, (Rectangle) {0.0, 0.0, (float) Properties::screenWidth, (float) Properties::screenHeight}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        
        // Move to other scenes
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is option title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);
        if(backButton.Check()) {
            state = PAUSE;
        }
    }
};
