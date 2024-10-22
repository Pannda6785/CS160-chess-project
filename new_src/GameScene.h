#include "raylib.h"
#include "Properties.h"
#include "Button.h"
#include "RenderUtilities.h"

class GameScene {
public:
    GameScene() { Init(); }
    ~GameScene() {}

    void Init() {
        state = RUNNING;
    }

    // Is called per frame. Controls the flow of the game scene.
    void Run() {
        ClearBackground(RAYWHITE);
        DrawLine(GetScreenHeight(), 0, GetScreenHeight(), GetScreenHeight(), BLACK);
        DrawText("This is the game, enjoy!", GetScreenHeight() + 30, 100, 25, RED);
        DrawText("Some information here for you nerds.", GetScreenHeight() + 30, 160, 15, LIGHTGRAY);
        game.Run();
    }

private:
    enum GAME_STATE {
        RUNNING,
        PAUSED,
        ENDED       
    }; 
    GAME_STATE state;
};
