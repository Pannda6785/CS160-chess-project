#include "raylib.h"
#include "Properties.h"

class Title {
    SCENE nextScene;
public:
    void Run();
    SCENE getScene();
};