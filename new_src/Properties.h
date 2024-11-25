#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <filesystem>
#include <array>
#include <map>
#include <string>
#include "raylib.h"
#include <iostream>

namespace Properties { // game properties
    // Window variables
    const int screenWidth[] = {1280, 1366, 1440};
    const int screenHeight[] = {800, 768, 900};
    inline bool isFullscreen = false;

    // Assets holders.
    inline std::map<std::string, Sound> sounds;
    inline std::map<std::string, Music> musics;
    inline std::map<std::string, Music> music1;
    inline std::map<std::string, Music> music2;
    inline std::map<std::string, Music> music3;
    inline std::map<std::string, Texture> skins;
    inline std::map<std::string, Texture> skin1;
    inline std::map<std::string, Texture> skin2;
    inline std::map<std::string, Texture> skin3;
    inline std::map<std::string, Texture> textures;
    inline std::map<std::string, Texture> elements;
    inline std::map<std::string, Font> fonts;
    inline int skin;
    inline bool isMusicPaused;
    inline std::string musicName;
    inline bool isMusicsMute, isSoundsMute;
    inline float musicsVolume, soundsVolume;
    inline int fontSizes[] = {20, 25, 45, 80};
    
    // Assets paths
    const std::string ASSETS_PATH = "../assets";
    const std::string SOUNDS_PATH = ASSETS_PATH + "/sounds"; // Sounds effects
    const std::string MUSIC1_PATH = ASSETS_PATH + "/musics/music1"; // Background musics
    const std::string MUSIC2_PATH = ASSETS_PATH + "/musics/music2"; // Background musics
    const std::string MUSIC3_PATH = ASSETS_PATH + "/musics/music3"; // Background musics
    const std::string SKIN1_PATH = ASSETS_PATH + "/textures/skin1"; // On-board elements (need to modified one)
    const std::string SKIN2_PATH = ASSETS_PATH + "/textures/skin2"; // On-board elements (need to modified one)
    const std::string SKIN3_PATH = ASSETS_PATH + "/textures/skin3"; // On-board elements (need to modified one)
    const std::string ELEMENTS_PATH = ASSETS_PATH + "/elements"; // titles element
    const std::string FONTS_PATH = ASSETS_PATH + "/fonts"; 
    const std::string SAVEFILES_PATH = "../savefiles";
    const std::string SAVEFILES_SLOT1 = SAVEFILES_PATH + "/slot1.txt";
    const std::string SAVEFILES_SLOT2 = SAVEFILES_PATH + "/slot2.txt";
    const std::string SAVEFILES_SLOT3 = SAVEFILES_PATH + "/slot3.txt";

    // Windows Info
    inline int GetBorderSize() {
        return GetScreenHeight() / 20;
    }
    inline int GetCellSize() {
        return GetScreenHeight() * 9 / 80;
    }

    inline void ToggleFullscreen(int screen) {
        if (screen == 3 && !isFullscreen) { // Toggle to fullscreen borderless mode
            isFullscreen = true;
            SetWindowState(FLAG_WINDOW_UNDECORATED);
            SetWindowPosition(0, 0);
            int monitor = GetCurrentMonitor();
            SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        }
        if(screen != 3) { // Toggle to fixed resolution
            isFullscreen = false;
            ClearWindowState(FLAG_WINDOW_UNDECORATED);
            int monitor = GetCurrentMonitor();
            int x = GetMonitorWidth(monitor) / 2 - screenWidth[screen] / 2;
            int y = GetMonitorHeight(monitor) / 2 - screenHeight[screen] / 2;
            SetWindowPosition(x, y);
            SetWindowSize(screenWidth[screen], screenHeight[screen]);
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

        // Initial values
        isSoundsMute = false;
        soundsVolume = 1.0f;
    }
    inline void LoadMusics() {
        SetAudioStreamBufferSizeDefault(131072);

        for (const auto & entry : std::filesystem::directory_iterator(MUSIC1_PATH)) {
            // Load sound.
            Music music = LoadMusicStream(entry.path().string().c_str());

            // Add sound to map of sounds.
            std::string fileName = entry.path().filename().string();
            size_t dotIndex = fileName.find('.');

            std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
            music1[fileNameWithoutExtension] = music;

            // Free sound data.
            // UnloadSound(sound);
        }
        for (const auto & entry : std::filesystem::directory_iterator(MUSIC2_PATH)) {
            // Load sound.
            Music music = LoadMusicStream(entry.path().string().c_str());

            // Add sound to map of sounds.
            std::string fileName = entry.path().filename().string();
            size_t dotIndex = fileName.find('.');

            std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
            music2[fileNameWithoutExtension] = music;

            // Free sound data.
            // UnloadSound(sound);
        }
        for (const auto & entry : std::filesystem::directory_iterator(MUSIC3_PATH)) {
            // Load sound.
            Music music = LoadMusicStream(entry.path().string().c_str());

            // Add sound to map of sounds.
            std::string fileName = entry.path().filename().string();
            size_t dotIndex = fileName.find('.');

            std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
            music3[fileNameWithoutExtension] = music;

            // Free sound data.
            // UnloadSound(sound);
        }

        // Initial values
        isMusicsMute = false;
        musicsVolume = 1.0f;
        musicName = "titleMusic";
        musics = music1;
        isMusicPaused = false;
    }

    inline void LoadTextures() {
        for (const auto & entry : std::filesystem::directory_iterator(SKIN1_PATH)) {
            // Load and resize image.
            Image image = LoadImage(entry.path().string().c_str());
            // ImageResize(&image, GetCellSize(), GetCellSize()); // No need now

            Texture texture = LoadTextureFromImage(image);

            // Add texture to map of textures.
            std::string fileName = entry.path().filename().string();
            size_t dotIndex = fileName.find('.');

            std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
            skin1[fileNameWithoutExtension] = texture;

            // Free image data.
            UnloadImage(image);
        }
        for (const auto & entry : std::filesystem::directory_iterator(SKIN2_PATH)) {
            // Load and resize image.
            Image image = LoadImage(entry.path().string().c_str());
            // ImageResize(&image, GetCellSize(), GetCellSize());
            

            Texture texture = LoadTextureFromImage(image);

            // Add texture to map of textures.
            std::string fileName = entry.path().filename().string();
            size_t dotIndex = fileName.find('.');

            std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
            skin2[fileNameWithoutExtension] = texture;

            // Free image data.
            UnloadImage(image);
        }
        for (const auto & entry : std::filesystem::directory_iterator(SKIN3_PATH)) {
            // Load and resize image.
            Image image = LoadImage(entry.path().string().c_str());
            // ImageResize(&image, GetCellSize(), GetCellSize());

            Texture texture = LoadTextureFromImage(image);

            // Add texture to map of textures.
            std::string fileName = entry.path().filename().string();
            size_t dotIndex = fileName.find('.');

            std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
            skin3[fileNameWithoutExtension] = texture;

            // Free image data.
            UnloadImage(image);
        }

        // default skin
        skin = 0;
        skins = skin1;
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

    inline std::string GetSavefilePath(int slot) {
        if (slot == 1) return SAVEFILES_SLOT1;
        if (slot == 2) return SAVEFILES_SLOT2;
        if (slot == 3) return SAVEFILES_SLOT3;
        return ""; // shoud not reach this
    }
    
    // Sound settings
    inline void SetSoundsVolume(float volume) {
        soundsVolume = volume;
        if(!isSoundsMute) {
            for(auto v : sounds) {
                SetSoundVolume(v.second, volume);
            }
        }
    }

    inline void MuteSounds() {
        if(!isSoundsMute) {
            isSoundsMute = true;
            for(auto v : sounds) {
                SetSoundVolume(v.second, 0.0f);
            }
        }
        else {
            isSoundsMute = false;
            for(auto v : sounds) {
                SetSoundVolume(v.second, soundsVolume);
            }
        }
    }

    inline void SetMusicsVolume(float volume) {
        musicsVolume = volume;
        if(!isMusicsMute) {
            for(auto v : musics) {
                SetMusicVolume(v.second, volume);
            }
        }
    }
    
    inline void MuteMusics() {
        if(!isMusicsMute) {
            isMusicsMute = true;
            for(auto v : musics) {
                SetMusicVolume(v.second, 0.0f);
            }
        }
        else {
            isMusicsMute = false;
            for(auto v : musics) {
                SetMusicVolume(v.second, musicsVolume);
            }
        }
    }

    inline void UpdateMusics() {
        UpdateMusicStream(musics[musicName]);
    }

    inline void ChangeMusic(std::string name) {
        StopMusicStream(musics[musicName]);
        musicName = name;
        PlayMusicStream(musics[musicName]);
    }

    inline void ChangeMusicBegin(std::string name) {
        PauseMusicStream(musics[musicName]);
        isMusicPaused = true;
        musicName = name;
        PlayMusicStream(musics[musicName]);
    }

    inline void ChangeMusicEnd(std::string name) {
        StopMusicStream(musics[musicName]);
        musicName = name;
        
        if(!isMusicPaused) StopMusicStream(musics[musicName]);
        PlayMusicStream(musics[musicName]);
    }

    // Chess' custom
    inline void changeSkin(int newSkin) {
        switch (newSkin) {
            case 0: {
                skins = skin1;
                skin = 0;
                musics = music1;
                isMusicPaused = false;
                SetMusicsVolume(musicsVolume);
                ChangeMusic(musicName);
            } break;
            case 1: {
                skins = skin2;
                skin = 1;
                musics = music2;
                isMusicPaused = false;
                SetMusicsVolume(musicsVolume);
                ChangeMusic(musicName);
            } break;
            case 2: {
                skins = skin3;
                skin = 2;
                musics = music3;
                isMusicPaused = false;
                SetMusicsVolume(musicsVolume);
                ChangeMusic(musicName);
            }
        }
    }
};

#endif //PROPERTIES_H