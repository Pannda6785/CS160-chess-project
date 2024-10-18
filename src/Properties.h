#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <string>
#include <map>
#include <filesystem>
#include "raylib.h"

enum GameScreen
{
    LOGO = 0,
    MAINMENU,
    MODEMENU,
    ONEPLAYER,
    TWOPLAYER,
    WINLOSE
};


class Properties {
public:
    // Windows Info
    const static int screenWidth = 1280;
    const static int screenHeight = 850;
    const static int cell_size = 80;
    static GameScreen currentScreen;

    // Assets holders.
    static std::map<std::string, Sound> sounds;
    static std::map<std::string, Texture> textures;

    // Load all assets
    void LoadSounds();
    void LoadTextures();
    void LoadMenu();

private:
    // Assets pathsx
    const std::string ASSETS_PATH = "../assets";
    const std::string SOUNDS_PATH = ASSETS_PATH + "/sounds"; // Sounds
    const std::string TEXTURES_PATH = ASSETS_PATH + "/textures"; // On-board elements (need to modified one)
    const std::string MENU_PATH = ASSETS_PATH + "/menu"; // Rests?
};

#endif //PROPERTIES_H
