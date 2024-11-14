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
    Button backLoadSaveButton;
    // pauseGame
    Button continueButton;
    Button saveButton;
    Button loadButton;
    Button optionsButton;
    Button undoButton;
    Button redoButton;
    Button exitButton;
    // saveGame
    Button save1Button;
    Button save2Button;
    Button save3Button;
    // loadGame
    Button load1Button;
    Button load2Button;
    Button load3Button;
    
    // List of gameScene
    void MainGame();
    void PauseGame();
    void SaveGame();
    void LoadGame();
    void OptionsGame();
};

extern GameScene gameScene;