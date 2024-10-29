#include "raylib.h"
#include "Properties.h"
#include "Button.h"
#include "RenderUtilities.h"
#include "vector"
#include "Game.h"

class TitleScene {
public:
    TitleScene() { Init(); }
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


    // duplicated buttons 
    Button backButton = Button(Rectangle{10, (float)GetScreenHeight() - 70, 180, 60}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Back", 45, LIME);

    Button newGameButton = Button(Rectangle{(float)GetScreenWidth() / 2 - 130, (float)GetScreenHeight() / 2 - 30, 260, 70}, LIGHTGRAY, Properties::textures[""], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "New Game", 45, LIME);
    Button loadButton = Button(Rectangle{(float)GetScreenWidth() / 2 - 130, (float)GetScreenHeight() * 5 / 8- 30, 260, 70}, LIGHTGRAY, Properties::textures[""], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Load", 45, LIME);
    Button optionsButton = Button(Rectangle{(float)GetScreenWidth() / 2 - 130, (float)GetScreenHeight() * 3 / 4 - 30, 260, 70}, LIGHTGRAY, Properties::textures[""], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Options", 45, LIME);
    Button exitButton = Button(Rectangle{(float)GetScreenWidth() / 2 - 130, (float)GetScreenHeight() * 7 / 8 - 30, 260, 70}, LIGHTGRAY, Properties::textures[""], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Exit", 45, LIME);
    void MainTitle() {
        // Render assets
        DrawTexturePro(Properties::elements["mainTitle"], (Rectangle) {0.0, 0.0, (float) Properties::elements["mainTitle"].width, (float) Properties::elements["mainTitle"].height}, (Rectangle) {0.0, 0.0, (float) Properties::screenWidth, (float) Properties::screenHeight}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "GAY CHESS", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);

        // Move to other scenes
        if (newGameButton.Check()) {
            title = MODE;
        }
        if(loadButton.Check()) {
            title = LOAD;
        }
        if(optionsButton.Check()) {
            title = OPTIONS;
        }
        if (exitButton.Check()) {
            ChangeScene(EXIT);
        }
    }

    Button onePlayerButton = Button(Rectangle{(float)GetScreenWidth() / 2 - 130, (float)GetScreenHeight() / 2 - 30, 260, 70}, LIGHTGRAY, Properties::textures[""], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "1 Player", 45, LIME);
    Button twoPlayerButton = Button(Rectangle{(float)GetScreenWidth() / 2 - 130, (float)GetScreenHeight() * 5 / 8- 30, 260, 70}, LIGHTGRAY, Properties::textures[""], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "2 Player", 45, LIME);
    void ModeTitle() {
        // Render assets
        DrawTexturePro(Properties::elements["mainTitle"], (Rectangle) {0.0, 0.0, (float) Properties::elements["mainTitle"].width, (float) Properties::elements["mainTitle"].height}, (Rectangle) {0.0, 0.0, (float) Properties::screenWidth, (float) Properties::screenHeight}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is one mode only. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 4), 80, 2, PINK);

        // Move to other scenes
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
        
        // Move to other scenes
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is difficulty title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 4), 80, 2, PINK);
        if(backButton.Check()) {
            title = MODE;
        }
    }

    void LoadTitle() {
        // Render assets
        DrawTexturePro(Properties::elements["loadBackGround"], (Rectangle) {0.0, 0.0, (float) Properties::elements["loadBackGround"].width, (float) Properties::elements["loadBackGround"].height}, (Rectangle) {0.0, 0.0, (float) Properties::screenWidth, (float) Properties::screenHeight}, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        DrawTexturePro(Properties::elements["box"], (Rectangle) {0.0, 0.0, (float) Properties::elements["box"].width, (float) Properties::elements["box"].height}, (Rectangle) {(float) Properties::screenWidth / 12, (float) Properties::screenHeight / 2, (float) Properties::screenWidth / 4, (float) Properties::screenHeight / 3}, (Vector2) {0.0, 0.0}, 0.0, WHITE);

        // Move to other scenes
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is load title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 4), 80, 2, PINK);
        if(backButton.Check()) {
            title = MAIN;
        }
    }

    void OptionsTitle() {
        // Render assets
        
        // Move to other scenes
        DrawTextCenEx(Properties::fonts["Rubik-Regular_80"], "There is option title. Sorry", int(GetScreenWidth() / 2), int(GetScreenHeight() / 4), 80, 2, PINK);
        if(backButton.Check()) {
            title = MAIN;
        }
    }
};