#include "Button.h"

class TitleScene {
public:
    void Init();
    void InitButtons();

    // Is called per frame. Controls the flow of the title scene.
    void Run();

private:
    // lists of pre-title for backButton
    enum TITLE {
        MAIN,
        MODE,
        DIFFICULTY,
        SAVE,
        LOAD,
        OPTIONS
    };
    TITLE title = MAIN;

    // List of buttons 
    Button backButton;
    // Main title buttons
    Button newGameButton;
    Button loadButton;
    Button optionsButton;
    Button exitButton;
    // Mode title buttons
    Button onePlayerButton;
    Button twoPlayerButton;
    Button backModeButton;
    // Difficulty title buttons
    Button easyDiffButton;
    Button mediumDiffButton;
    Button hardDiffButton;
    Button backDiffButton;

    // List of TitleScene;
    void MainTitle();
    void ModeTitle() ;
    void DifficultyTitle();
    void LoadTitle();
    void OptionsTitle();
};

extern TitleScene titleScene;