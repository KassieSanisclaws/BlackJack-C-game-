#pragma once

#include <string>
#include <vector>

#include "Vector2D.h"
#include "GameObjectSettings.h"

class SceneSettings
{
public:
    SceneSettings(const SceneSettings&) = delete;
    ~SceneSettings();

    static SceneSettings* getInstance();
    static void removeInstance();

    SceneSettings& operator=(const SceneSettings&) = delete;

    std::string sceneID;
    std::vector<GameObjectSettings> objects;

private:
    SceneSettings();

    static SceneSettings* instance;
};