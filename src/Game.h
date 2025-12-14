#pragma once

#include <SDL2/SDL.h>
#include "Logger.h"
#include "ECS/Registry.h"
#include "AssetStore/AssetStore.h"

class Game {

    const int FPS = 60;
    const int FRAME_MILLISECONDS = 1000/FPS;

    SDL_Window *window;
    SDL_Renderer* renderer;
    bool isRunning = false;

    Uint32 lastUpdateTime = 0;
    std::unique_ptr<Registry> registry;
    std::unique_ptr<AssetStore> asserStore;

    Logger logger;


    void ProcessEvents();
    void Render();
    void Update();

    void SpawnEntities();
public:
    Game();

    ~Game();

    void Run();
};
