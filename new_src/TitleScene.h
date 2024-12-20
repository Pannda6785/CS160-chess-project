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

    // List of TitleScene;
    void MainTitle();
    void ModeTitle() ;
    void DifficultyTitle();
    void OnePlayerTitle();
    void LoadTitle();
    void OptionsTitle();
};

extern TitleScene titleScene;