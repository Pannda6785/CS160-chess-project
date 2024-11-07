#include "raylib.h"

#include "Button.h"

class TitleScene {
public:
    TitleScene();
    ~TitleScene();

    void Init();

    // Is called per frame. Controls the flow of the title scene.
    void Run();

private:
    enum TITLE {
        MAIN,
        MODE,
        DIFFICULTY,
        SAVE,
        LOAD,
        OPTIONS
    };

    // lists of pre-title for backButton
    TITLE title;

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

    void InitButtons();

    // List of TitleScene;
    void MainTitle();
    void ModeTitle() ;
    void DifficultyTitle();
    void LoadTitle();
    void OptionsTitle();
};