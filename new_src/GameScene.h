#include "Button.h"

class GameScene {
public:
    void Init();
    void InitButtons();

    // Is called per frame. Controls the flow of the game scene.
    void Run();

private:
    // Current mode game and scene
    enum GAME_STATE {
        MAIN,
        PAUSE,
        SAVE,
        LOAD,
        OPTIONS,
        ENDED       
    }; 
    GAME_STATE state = MAIN;

    // List of buttons
    Button backButton;
    Button continueButton;
    Button saveButton;
    Button loadButton;
    Button optionsButton;
    Button undoButton;
    Button redoButton;
    
    // TESTING
    Button testSaveButton;
    Button testLoadButton;
    
    // List of gameScene
    void MainGame();
    void PauseGame();
    void SaveGame();
    void LoadGame();
    void OptionsGame();
};

extern GameScene gameScene;