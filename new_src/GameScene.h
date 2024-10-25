#include "raylib.h"
#include "Properties.h"
#include "Button.h"
#include "RenderUtilities.h"
#include <vector>
#include "game.h"

class GameScene {
public:
    GameScene() { Init(); }
    ~GameScene() {}

    void Init() {
        if(states.empty()) {
            state = RUNNING;
        }
        else {
            state = states.back();
        }
    }

    // Is called per frame. Controls the flow of the game scene.
    Button backButton = Button(Rectangle{10, (float)GetScreenHeight() - 70, 180, 60}, WHITE, Properties::elements["button"], Properties::sounds["buttonClick"], Properties::fonts["Rubik-Regular_45"], "Back", 45, LIME);

    void Run() {
        ClearBackground(RAYWHITE);

        // Side panel
        // Background
        DrawLine(GetScreenHeight(), 0, GetScreenHeight(), GetScreenHeight(), BLACK);
        DrawTexturePro(Properties::elements["lmao"], (Rectangle) {0.0, 0.0, (float) Properties::elements["lmao"].width, (float) Properties::elements["lmao"].height}, (Rectangle) {0.0, 0.0, (float) Properties::screenWidth, (float) Properties::screenHeight}, (Vector2) {0.0, 0.0}, 0.0, WHITE);

        // Text box
        DrawText("This is the game, enjoy!", GetScreenHeight() + 30, 100, 25, RED);
        DrawText("Some information here for you nerds.", GetScreenHeight() + 30, 160, 15, LIGHTGRAY);

        game.Run();
        if(backButton.Check()) {
            ChangeScene(TITLE_SCENE);
        }
    }

private:
    enum GAME_STATE {
        RUNNING,
        PAUSED,
        ENDED       
    }; 

    
    Game game;
    GAME_STATE state;
    std::vector<GAME_STATE> states;
};
