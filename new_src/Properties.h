#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <filesystem>
#include <array>
#include <map>
#include <string>
#include "raylib.h"

constexpr int BOARD_SIZE = 8;
typedef std::array<std::array<int, BOARD_SIZE>, BOARD_SIZE> Board;

enum SCENE {
    TITLESCENE,
    GAMESCENE
};

namespace Properties { // game properties
    // Windows Info
    const static int screenWidth = 1280;
    const static int screenHeight = 850;
    const static int cell_size = 80;

    // Assets holders.
    static std::map<std::string, Sound> sounds;
    static std::map<std::string, Texture> textures;

    // Load all assets
    void LoadSounds();
    void LoadTextures();
    void LoadMenu();

    // Moves
    static std::string position;
    static std::string toChessNode();
    
    // Assets pathsx
    const std::string ASSETS_PATH = "../assets";
    const std::string SOUNDS_PATH = ASSETS_PATH + "/sounds"; // Sounds
    const std::string TEXTURES_PATH = ASSETS_PATH + "/textures"; // On-board elements (need to modified one)
    const std::string MENU_PATH = ASSETS_PATH + "/menu"; // Rests?
};

#endif //PROPERTIES_H