#pragma once

#include <SDL2/SDL.h>
#include "Logger.h"

class Game {

    const int FPS = 60;
    const int FRAME_MILLISECONDS = 1000/FPS;

    SDL_Window *window;
    SDL_Renderer* renderer;
    bool isRunning = false;

    Uint32 lastUpdateTime = 0;
    Logger logger;

    void ProcessEvents();
    void Render();
    void Update();
public:
    Game();

    ~Game();

    void Run();
};
