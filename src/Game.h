#pragma once

#include <SDL2/SDL.h>

class Game {

    SDL_Window *window;
    SDL_Renderer* renderer;
    bool isRunning = false;

    void ProcessEvents();
    void Render();
public:
    Game();

    ~Game();

    void Run();
};
