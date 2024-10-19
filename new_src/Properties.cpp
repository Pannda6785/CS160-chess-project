// #include "Properties.h"

// void Properties::LoadSounds() {
//     for (const auto & entry : std::filesystem::directory_iterator(SOUNDS_PATH)) {
//         // Load sound.
//         Sound sound = LoadSound(entry.path().string().c_str());

//         // Add sound to map of sounds.
//         std::string fileName = entry.path().filename().string();
//         size_t dotIndex = fileName.find('.');

//         std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
//         sounds[fileNameWithoutExtension] = sound;
//     }
// }

// void Properties::LoadTextures() {
//     for (const auto & entry : std::filesystem::directory_iterator(TEXTURES_PATH)) {
//         // Load and resize image.
//         Image image = LoadImage(entry.path().string().c_str());
//         ImageResize(&image, cell_size, cell_size);

//         Texture texture = LoadTextureFromImage(image);

//         // Add texture to map of textures.
//         std::string fileName = entry.path().filename().string();
//         size_t dotIndex = fileName.find('.');

//         std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
//         textures[fileNameWithoutExtension] = texture;

//         // Free image data.
//         UnloadImage(image);
//     }
// }

// void Properties::LoadMenu() {
//     for (const auto & entry : std::filesystem::directory_iterator(TEXTURES_PATH)) {
//         // Load and resize image.
//         Image image = LoadImage(entry.path().string().c_str());
//         Texture texture = LoadTextureFromImage(image);

//         // Add texture to map of textures.
//         std::string fileName = entry.path().filename().string();
//         size_t dotIndex = fileName.find('.');

//         std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
//         textures[fileNameWithoutExtension] = texture;

//         // Free image data.
//         UnloadImage(image);
//     }
// }