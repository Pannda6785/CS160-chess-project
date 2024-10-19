#include "raylib.h"
#include "Properties.h"

class Game {
    Board board;
public:
    void Run() {
        ClearBackground(RAYWHITE);
        DrawText("This is the game, enjoy!", 190, 200, 20, RED);
    }
};
