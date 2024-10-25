#ifndef TITLE_H
#define TITLE_H

#include "bits/stdc++.h"

enum MENU {
    MAINMENU = 0,
    SAVEMENU,
    LOADMENU,
    MODEMENU,
    
    OPTIONMENU,
};

class Title {
public:
    /*
    Title();
    ~Title();
    */

    void Run();
    void MainMenu();
    void SaveGame();
    void LoadGame();
    void Options();
private:
    MENU current;
};

#endif //TITLE_H