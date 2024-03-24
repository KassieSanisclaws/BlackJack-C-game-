#pragma once

#include <string>

class GameSettings 
{
public:
    GameSettings(const GameSettings&) = delete;
    ~GameSettings();

    static GameSettings* getInstance();
    static void removeInstance();

    GameSettings& operator=(const GameSettings&) = delete;

    bool fullscreen;
    
    std::string title;
    std::string gameloop;
    std::string renderer;

    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;

private:
    GameSettings();

    static GameSettings* instance;    
};