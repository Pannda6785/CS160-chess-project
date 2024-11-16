#include "Button.h"
#include "Slider.h"

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
        ONEPLAYER,
        SAVE,
        LOAD,
        OPTIONS
    };
    TITLE title = MAIN;
    bool isWhite = 0;

    // List of buttons 
    Button backButton;
    Button backModeButton;
    Button backLoadSaveButton;
    // Main title buttons
    Button newGameButton;
    Button loadButton;
    Button optionsButton;
    Button exitButton;
    // Mode title buttons
    Button onePlayerButton;
    Button twoPlayerButton;
    // Difficulty title buttons
    Button easyDiffButton;
    Button mediumDiffButton;
    Button hardDiffButton;
    Button backDiffButton;
    // 1 player title buttons
    Button chooseWhiteButton;
    Button chooseBlackButton;
    // Save title buttons
    Button load1Button;
    Button load2Button;
    Button load3Button;
    // Option title buttons
    Slider musicsVolume;
    Slider soundsVolume;

    // List of TitleScene;
    void MainTitle();
    void ModeTitle() ;
    void DifficultyTitle();
    void OnePlayerTitle();
    void LoadTitle();
    void OptionsTitle();
};

extern TitleScene titleScene;