#include "SceneSettings.h"

SceneSettings::SceneSettings()
{

}

SceneSettings::~SceneSettings()
{

}

SceneSettings* SceneSettings::getInstance()
{
    if (instance == nullptr)
        instance = new SceneSettings();

    return instance;
}

void SceneSettings::removeInstance()
{
    if (instance)
        delete instance;
}

SceneSettings* SceneSettings::instance = nullptr;
