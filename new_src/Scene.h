#ifndef SCENE_H
#define SCENE_H

namespace Scene {
    enum SCENE {
        EXIT,
        TITLE_SCENE,
        GAME_SCENE
    };
    
    inline SCENE scene;
    inline bool isSceneChanged;

    inline bool ChangeScene(SCENE newScene) {
        if (newScene == scene) return false;
        scene = newScene;
        isSceneChanged = true;
        return true;
    }
}

#endif // SCENE_H

