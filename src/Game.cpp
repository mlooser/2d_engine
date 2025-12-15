#include "Game.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SDL2/SDL_image.h>

#include "Components/RigidBody.h"
#include "Components/Transform.h"
#include "Components/SpriteAnimation.h"
#include "Systems/AnimationSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/RenderingSystem.h"

struct SpriteAnimation;

Game::Game() {
    registry = std::make_unique<Registry>(&logger);


    if (SDL_Init(SDL_INIT_EVERYTHING)!=0) {
        logger.Error("SDL_Init Error: " + std::string(SDL_GetError()));
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    window = SDL_CreateWindow(
        "My game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        displayMode.w,
        displayMode.h,
        SDL_WINDOW_SHOWN);

    if (!window) {
        logger.Error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1,0);
    if (!renderer) {
        logger.Error("SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    isRunning = true;

    lastUpdateTime = SDL_GetTicks();

    asserStore = std::make_unique<AssetStore>(renderer);

    SpawnEntities();
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    logger.Info("Game::~Game");
}

void Game::Run() {
    while (isRunning) {
        ProcessEvents();
        Update();
        Render();
    }
}

void Game::ProcessEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
                break;
            default: ;
        }
    }
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    registry->GetSystem<RenderingSystem>().Render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::Update() {
    Uint32 deltaTicks = SDL_GetTicks() - lastUpdateTime;
    Uint32 timeToWait = FRAME_MILLISECONDS - deltaTicks;
    if (timeToWait>0 && timeToWait < FRAME_MILLISECONDS) {
        SDL_Delay(timeToWait);
    }

    Uint32 nowTicks = SDL_GetTicks();
    deltaTicks = nowTicks - lastUpdateTime;
    lastUpdateTime = nowTicks;

    float deltaTime = static_cast<float>(deltaTicks) / 1000.f;
    registry->GetSystem<AnimationSystem>().Update(deltaTime);
    registry->GetSystem<MovementSystem>().Update(deltaTime);

    registry->Update();
}

void Game::SpawnEntities() {

    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderingSystem>(asserStore.get());
    registry->AddSystem<AnimationSystem>();

    Entity chopper = registry->CreateEntity();

    registry->AddComponent<Transform>(chopper, glm::vec2(10,10), glm::vec2(3,3));
    registry->AddComponent<RigidBody>(chopper, glm::vec2(30, 30));
    registry->AddComponent<Sprite>(chopper, "chopper", 32, 32, 0, 0, 2);
    registry->AddComponent<SpriteAnimation>(chopper, 2, 10, true);

    registry->AddEntityToSystems(chopper);

    LoadTileMap();
}

void Game::LoadTileMap() {
    std::ifstream mapFile("./assets/tilemaps/jungle.map");
    if (!mapFile.is_open()) {
        logger.Error("Failed to open jungle.map");
        return;
    }

    const int tileSize = 32;
    const int tilemapColumns = 10;

    double scale = 2.0;
    glm::vec2 tileScale = glm::vec2(scale, scale);

    std::string line;
    int row = 0;

    while (std::getline(mapFile, line)) {
        std::stringstream ss(line);
        std::string token;
        int col = 0;

        while (std::getline(ss, token, ',')) {
            int tileId = std::stoi(token);

            int srcX = (tileId % tilemapColumns) * tileSize;
            int srcY = (tileId / tilemapColumns) * tileSize;

            int dstX = col * tileSize * scale;
            int dstY = row * tileSize * scale;

            Entity tile = registry->CreateEntity();
            registry->AddComponent<Transform>(tile, glm::vec2(dstX, dstY), tileScale);
            registry->AddComponent<Sprite>(tile, "tilemap-image", tileSize, tileSize, srcX, srcY, 0);
            registry->AddEntityToSystems(tile);

            col++;
        }
        row++;
    }

    mapFile.close();
}


