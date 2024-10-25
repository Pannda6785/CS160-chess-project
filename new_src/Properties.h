#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <filesystem>
#include <array>
#include <map>
#include <string>
#include "raylib.h"

enum SCENE {
    EXIT,
    TITLE_SCENE,
    GAME_SCENE
};
SCENE scene;
bool isSceneChanged;

bool ChangeScene(SCENE newScene) {
    if (newScene == scene) return false;
    scene = newScene;
    isSceneChanged = true;
    return true;
} 

namespace Properties { // game properties
    // Windows Info
    int screenWidth = 1280;
    int screenHeight = 850;
    int borderSize = screenHeight/20;
    int cellSize = screenHeight*9/80;

    // Assets holders.
    std::map<std::string, Sound> sounds;
    std::map<std::string, Texture> textures;
    std::map<std::string, Texture> elements;
    std::map<std::string, Font> fonts;
    int fontSizes[] = {45, 80};
    
    // Assets paths
    const std::string ASSETS_PATH = "../assets";
    const std::string SOUNDS_PATH = ASSETS_PATH + "/sounds"; // Sounds
    const std::string TEXTURES_PATH = ASSETS_PATH + "/textures"; // On-board elements (need to modified one)
    const std::string ELEMENTS_PATH = ASSETS_PATH + "/elements"; // titles element
    const std::string FONTS_PATH = ASSETS_PATH + "/fonts/rubik"; // fonts element

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
            // UnloadSound(sound);
        }
    }
    void LoadTextures() {
        for (const auto & entry : std::filesystem::directory_iterator(TEXTURES_PATH)) {
            // Load and resize image.
            Image image = LoadImage(entry.path().string().c_str());
            ImageResize(&image, cellSize, cellSize);

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
    void LoadElements() {
        for (const auto & entry : std::filesystem::directory_iterator(ELEMENTS_PATH)) {
            // Load and resize image.
            Image image = LoadImage(entry.path().string().c_str());
            Texture texture = LoadTextureFromImage(image);

            // Add texture to map of textures.
            std::string fileName = entry.path().filename().string();
            size_t dotIndex = fileName.find('.');

            std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
            elements[fileNameWithoutExtension] = texture;

            // Free image data.
            UnloadImage(image);
        }
    }
    void LoadFonts() {
        for (const auto & entry : std::filesystem::directory_iterator(FONTS_PATH)) {
            for(const auto & fontSize : fontSizes) {
                // Load font.
                Font font = LoadFontEx(entry.path().string().c_str(), fontSize, 0, 0);

                // Add font to map of fonts.
                std::string fileName = entry.path().filename().string();
                size_t dotIndex = fileName.find('.');

                std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex) + "_" + std::to_string(fontSize);
                fonts[fileNameWithoutExtension] = font;

                // Free font data.
                // UnloadFont(font);
            }
        }
    }
};

#endif //PROPERTIES_H