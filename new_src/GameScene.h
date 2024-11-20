#include "Button.h"
#include "Slider.h"

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
    // baseGame
    int scrollOffSet = 0;
    // mainGame
    Button newGameButton;
    Button moveBackButton;
    Button moveForwardButton;
    Button settingsButton;
    // pauseGame
    Button continueButton;
    Button saveButton;
    Button loadButton;
    Button optionsButton;
    Button exitButton;
    // saveGame
    Button save1Button;
    Button save2Button;
    Button save3Button;
    // loadGame
    Button load1Button;
    Button load2Button;
    Button load3Button;
    // Option title buttons
    Button resolution1Button;
    Button resolution2Button;
    Button resolution3Button;
    Button resolution4Button;
    Button skin1Button;
    Button skin2Button;
    Button skin3Button;
    Button leftButton;
    Button rightButton;
    Button muteMusicsButton;
    Button muteSoundsButton;
    Slider musicsVolume;
    Slider soundsVolume;
    Button backOptionsButton;
    
    // base Game
    void BaseGame();

    // List of gameScene
    void MainGame();
    void PauseGame();
    void SaveGame();
    void LoadGame();
    void OptionsGame();
    void EndGame();
};

extern GameScene gameScene;