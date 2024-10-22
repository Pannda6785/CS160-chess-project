#include "raylib.h"
#include "Properties.h"
#include "Button.h"
#include "RenderUtilities.h"

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
            default: break;
        }
    }

private:
    enum TITLE {
        MAIN,
        MODE,
        DIFFICULTY,
        LOAD,
        OPTIONS
    };

    TITLE title;

    Button newGameButton = Button(Rectangle{(float)GetScreenWidth() / 2 - 130, (float)GetScreenHeight() / 2 - 30, 260, 70}, LIGHTGRAY, "New Game", 45, LIME);
    Button exitButton = Button(Rectangle{(float)GetScreenWidth() / 2 - 130, (float)GetScreenHeight() * 3 / 4 - 30, 260, 70}, LIGHTGRAY, "Exit", 45, LIME);
    void MainTitle() {
        DrawTextCen("GAY CHESS", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, PINK);
        if (newGameButton.Check()) {
            title = MODE;
        }
        if (exitButton.Check()) {
            scene = EXIT;
        }
    }

    Button backButton = Button(Rectangle{10, (float)GetScreenHeight() - 70, 180, 60}, LIGHTGRAY, "Back", 45, WHITE);
    Button twoPlayerButton = Button(Rectangle{(float)GetScreenWidth() / 2 - 130, (float)GetScreenHeight() / 2 - 30, 260, 70}, LIGHTGRAY, "2 Player", 45, LIME);
    void ModeTitle() {
        DrawTextCen("There is only one mode. Sorry.", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, PINK);
        if (backButton.Check()) {
            title = MAIN;
        }
        if (twoPlayerButton.Check()) {
            scene = GAME_SCENE;
        }
    }

};