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

    // Update current elements
    void Update() {
        backButton = Button(Rectangle{10, (float)Properties::screenHeight - 70, 180, 60}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Back", 45, LIME);
        backButtonMain = Button(Rectangle{10, (float)Properties::screenHeight - 70, 180, 60}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Back", 45, LIME);
        continueButton = Button(Rectangle{(float)Properties::screenWidth / 2 - 130, (float)Properties::screenHeight * 3 / 8 - 30, 260, 70}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Continue", 45, LIME);
        saveButton = Button(Rectangle{(float)Properties::screenWidth / 2 - 130, (float)Properties::screenHeight / 2 - 30, 260, 70}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Save", 45, LIME);
        loadButton = Button(Rectangle{(float)Properties::screenWidth / 2 - 130, (float)Properties::screenHeight * 5 / 8- 30, 260, 70}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Load", 45, LIME);
        optionsButton = Button(Rectangle{(float)Properties::screenWidth / 2 - 130, (float)Properties::screenHeight * 3 / 4 - 30, 260, 70}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Options", 45, LIME);
        exitToMainMenu = Button(Rectangle{(float)Properties::screenWidth / 2 - 130, (float)Properties::screenHeight * 7 / 8 - 30, 260, 70}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Exit to main menu", 45, LIME);

    }

    // Is called per frame. Controls the flow of the game scene.
    void Run() {
        ClearBackground(RAYWHITE);
        switch(state) {
            case MAIN: {
                MainGame();
            }; break;
            case PAUSE: {
                MainGame();
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
    Button backButton = Button(Rectangle{10, (float)Properties::screenHeight - 70, 180, 60}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Back", 45, LIME);

    Button backButtonMain = Button(Rectangle{10, (float)Properties::screenHeight - 70, 180, 60}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Back", 45, LIME);
    void MainGame() {
        // Side panel
        // Background
        DrawLine(Properties::screenHeight, 0, Properties::screenHeight, Properties::screenHeight, BLACK);
        DrawTexturePro(Properties::elements["gameBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, (Rectangle) {0.0, 0.0, (float) Properties::screenWidth, (float) Properties::screenHeight}, (Vector2) {0.0, 0.0}, 0.0, WHITE);

        // Text box
        DrawRectangleRec((Rectangle) {(float) Properties::screenHeight + Properties::borderSize, (float) Properties::borderSize, (float) Properties::screenWidth - Properties::screenHeight - 2 * Properties::borderSize, (float) Properties::screenWidth - Properties::screenHeight - Properties::borderSize}, WHITE);
        // DrawRectangleRec((Rectangle) {(float) Properties::screenHeight + Properties::borderSize, (float) Properties::borderSize, (float) Properties::screenWidth - Properties::screenHeight - 2 * Properties::borderSize, (float) Properties::screenWidth - Properties::screenHeight - Properties::borderSize}, WHITE);
        DrawTextEx(Properties::fonts["Rubik-Regular_25"], "This is the game, enjoy!", (Vector2) {(float) Properties::screenHeight + 30 , (float) 100}, 25, 2, RED);
        DrawText("Some information here for you nerds.", Properties::screenHeight + 30, 160, 15, WHITE);

        game.Run();
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            state = PAUSE;
        }
        if(state == MAIN) {
            if(backButtonMain.Check()) {
                ChangeScene(TITLE_SCENE);
            }
        }
        else {
            backButton.Render();
            PauseGame();
        }
    }

    Button continueButton = Button(Rectangle{(float)Properties::screenWidth / 2 - 130, (float)Properties::screenHeight * 3 / 8 - 30, 260, 70}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Continue", 45, LIME);
    Button saveButton = Button(Rectangle{(float)Properties::screenWidth / 2 - 130, (float)Properties::screenHeight / 2 - 30, 260, 70}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Save", 45, LIME);
    Button loadButton = Button(Rectangle{(float)Properties::screenWidth / 2 - 130, (float)Properties::screenHeight * 5 / 8- 30, 260, 70}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Load", 45, LIME);
    Button optionsButton = Button(Rectangle{(float)Properties::screenWidth / 2 - 130, (float)Properties::screenHeight * 3 / 4 - 30, 260, 70}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Options", 45, LIME);
    Button exitToMainMenu = Button(Rectangle{(float)Properties::screenWidth / 2 - 130, (float)Properties::screenHeight * 7 / 8 - 30, 260, 70}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Exit to main menu", 45, LIME);
    void PauseGame() {
        // Render assets
        // Draw the tint over the background
        DrawRectangle(0, 0, Properties::screenWidth, Properties::screenHeight, (Color){0, 0, 0, 50}); // Dark overlay
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is pause title. Sorry", int(Properties::screenWidth / 2), int(Properties::screenHeight / 3), 80, 2, PINK);
        
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
        if(exitToMainMenu.Check()) {
            ChangeScene(TITLE_SCENE);
        }
    }

    void SaveGame() {
        // Render assets
        DrawTexturePro(Properties::elements["saveBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, (Rectangle) {0.0, 0.0, (float) Properties::screenWidth, (float) Properties::screenHeight}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, (Rectangle) {(float) Properties::screenWidth / 12, (float) Properties::screenHeight / 3, (float) Properties::screenWidth / 4, (float) Properties::screenHeight / 2}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, (Rectangle) {(float) Properties::screenWidth * 3 / 8, (float) Properties::screenHeight / 3, (float) Properties::screenWidth / 4, (float) Properties::screenHeight / 2}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, (Rectangle) {(float) Properties::screenWidth * 2 / 3, (float) Properties::screenHeight / 3, (float) Properties::screenWidth / 4, (float) Properties::screenHeight / 2}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is save title. Sorry", int(Properties::screenWidth / 2), int(Properties::screenHeight / 3), 80, 2, PINK);

        // Move to other scenes
        if(backButton.Check()) {
            state = PAUSE;
        }
    }

    void LoadGame() {
        // Render assets
        DrawTexturePro(Properties::elements["loadBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, (Rectangle) {0.0, 0.0, (float) Properties::screenWidth, (float) Properties::screenHeight}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, (Rectangle) {(float) Properties::screenWidth / 12, (float) Properties::screenHeight / 3, (float) Properties::screenWidth / 4, (float) Properties::screenHeight / 2}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, (Rectangle) {(float) Properties::screenWidth * 3 / 8, (float) Properties::screenHeight / 3, (float) Properties::screenWidth / 4, (float) Properties::screenHeight / 2}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, (Rectangle) {(float) Properties::screenWidth * 2 / 3, (float) Properties::screenHeight / 3, (float) Properties::screenWidth / 4, (float) Properties::screenHeight / 2}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is load title. Sorry", int(Properties::screenWidth / 2), int(Properties::screenHeight / 3), 80, 2, PINK);

        // Move to other scenes
        if(backButton.Check()) {
            state = PAUSE;
        }
    }
    
    void OptionsGame() {
        // Render assets
        DrawTexturePro(Properties::elements["optionsBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["gameBackGround"].width, (float) Properties::elements["gameBackGround"].height}, (Rectangle) {0.0, 0.0, (float) Properties::screenWidth, (float) Properties::screenHeight}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is option title. Sorry", int(Properties::screenWidth / 2), int(Properties::screenHeight / 3), 80, 2, PINK);
        
        // Move to other scenes
        if(backButton.Check()) {
            state = PAUSE;
        }
    }
};
