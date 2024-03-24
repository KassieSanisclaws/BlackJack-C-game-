#pragma once

class GameLoop 
{
public:
    virtual ~GameLoop() = default;

    virtual void process() = 0;

    virtual void handleEvents();
    virtual void update();
    virtual void render();

    bool isRunning();
    bool isPaused();

    long getStartTime();
    float getDeltaTime();

    bool running;
    bool paused;

    static const float FPS;
    static const float DELAY_TIME;

protected:
    long startTime;
    long currentTime;
    long previousTime;
    float delta;
};