#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <filesystem>
#include <array>
#include <map>
#include <string>
#include "raylib.h"
#include "Game.h"

enum SCENE {
    EXIT,
    TITLE_SCENE,
    GAME_SCENE
};
SCENE scene;
Game game;

namespace Properties { // game properties
    // Windows Info
    const static int screenWidth = 1280;
    const static int screenHeight = 850;
    const static int cell_size = 80;

    // Assets holders.
    static std::map<std::string, Sound> sounds;
    static std::map<std::string, Texture> textures;
    
    // Assets pathsx
    const std::string ASSETS_PATH = "../assets";
    const std::string SOUNDS_PATH = ASSETS_PATH + "/sounds"; // Sounds
    const std::string TEXTURES_PATH = ASSETS_PATH + "/textures"; // On-board elements (need to modified one)
    const std::string MENU_PATH = ASSETS_PATH + "/menu"; // Rests?

    // Load all assets
    void LoadSounds() {
        for (const auto & entry : std::filesystem::directory_iterator(SOUNDS_PATH)) {
            // Load sound.
            Sound sound = LoadSound(entry.path().string().c_str());

            // Add sound to map of sounds.
            std::string fileName = entry.path().filename().string();
            size_t dotIndex = fileName.find('.');

            std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
            sounds[fileNameWithoutExtension] = sound;

            // Free sound data.
            UnloadSound(sound);
        }
    }
    void LoadTextures() {
        for (const auto & entry : std::filesystem::directory_iterator(TEXTURES_PATH)) {
            // Load and resize image.
            Image image = LoadImage(entry.path().string().c_str());
            ImageResize(&image, cell_size, cell_size);

            Texture texture = LoadTextureFromImage(image);

            // Add texture to map of textures.
            std::string fileName = entry.path().filename().string();
            size_t dotIndex = fileName.find('.');

            std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
            textures[fileNameWithoutExtension] = texture;

            // Free image data.
            UnloadImage(image);
        }
    }
    void LoadMenu() {
        for (const auto & entry : std::filesystem::directory_iterator(TEXTURES_PATH)) {
            // Load and resize image.
            Image image = LoadImage(entry.path().string().c_str());
            Texture texture = LoadTextureFromImage(image);

            // Add texture to map of textures.
            std::string fileName = entry.path().filename().string();
            size_t dotIndex = fileName.find('.');

            std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
            textures[fileNameWithoutExtension] = texture;

            // Free image data.
            UnloadImage(image);
        }
    }
};

#endif //PROPERTIES_H