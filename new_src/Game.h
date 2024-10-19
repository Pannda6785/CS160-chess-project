#include "raylib.h"
#include "Properties.h"
#include <stack>

class Game {
    SCENE nextScene;
    Board board;
    std::stack<Board> history;
    std::stack<Board> redoHistory;
public:
    void Run();
    SCENE getScene();
};