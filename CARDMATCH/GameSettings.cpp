#include "GameSettings.h"

GameSettings::GameSettings()
{

}

GameSettings::~GameSettings()
{

}

GameSettings* GameSettings::getInstance() 
{
    if (instance == nullptr) 
        instance = new GameSettings();

    return instance;
}

void GameSettings::removeInstance()
{
    if (instance)
        delete instance;
}

int GameSettings::SCREEN_WIDTH = 0;
int GameSettings::SCREEN_HEIGHT = 0;

GameSettings* GameSettings::instance = nullptr;
