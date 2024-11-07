#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <filesystem>
#include <array>
#include <map>
#include <string>
#include "raylib.h"

namespace Properties { // game properties
    // Window variables
    const    int initialScreenWidth = 1280;
    const int initialScreenHeight = 720;
    inline bool isFullscreen = false;

    // Assets holders.
    inline std::map<std::string, Sound> sounds;
    inline std::map<std::string, Texture> textures;
    inline std::map<std::string, Texture> elements;
    inline std::map<std::string, Font> fonts;
    inline int fontSizes[] = {45, 80};
    
    // Assets paths
    const std::string ASSETS_PATH = "../assets";
    const std::string SOUNDS_PATH = ASSETS_PATH + "/sounds"; // Sounds
    const std::string TEXTURES_PATH = ASSETS_PATH + "/textures"; // On-board elements (need to modified one)
    const std::string ELEMENTS_PATH = ASSETS_PATH + "/elements"; // titles element
    const std::string FONTS_PATH = ASSETS_PATH + "/fonts"; // fonts element

    // Windows Info
    inline int GetInitialScreenWidth() {
        return initialScreenWidth;
    }
    inline int GetInitialScreenHeight() {
        return initialScreenHeight;
    }
    inline int GetBorderSize() {
        return GetScreenHeight() / 20;
    }
    inline int GetCellSize() {
        return GetScreenHeight() * 9 / 80;
    }

    inline void ToggleFullscreen() {
        if (!isFullscreen) {
            isFullscreen = true;
            SetWindowState(FLAG_WINDOW_UNDECORATED);
            SetWindowPosition(0, 0);
            int monitor = GetCurrentMonitor();
            SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        } else {
            isFullscreen = false;
            ClearWindowState(FLAG_WINDOW_UNDECORATED);
            int monitor = GetCurrentMonitor();
            int x = GetMonitorWidth(monitor) / 2 - GetInitialScreenWidth() / 2;
            int y = GetMonitorHeight(monitor) / 2 - GetInitialScreenHeight() / 2;
            SetWindowPosition(x, y);
            SetWindowSize(Properties::GetInitialScreenWidth(), Properties::GetInitialScreenHeight());
        }
    }


    // Load all assets
    inline void LoadSounds() {
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
    inline void LoadTextures() {
        for (const auto & entry : std::filesystem::directory_iterator(TEXTURES_PATH)) {
            // Load and resize image.
            Image image = LoadImage(entry.path().string().c_str());
            ImageResize(&image, GetCellSize(), GetCellSize());

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
    inline void LoadElements() {
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
    inline void LoadFonts() {
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