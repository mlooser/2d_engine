#include "Game.h"

#include <iostream>
#include <SDL2/SDL_image.h>

#include "Components/RigidBody.h"
#include "Components/Transform.h"
#include "Systems/MovementSystem.h"

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

    SDL_Surface* tank = IMG_Load("./assets/images/tank-tiger-right.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tank);
    SDL_FreeSurface(tank);

    SDL_Rect rect = {10, 10, 32, 32};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
}

void Game::Update() {
    Uint32 delta = SDL_GetTicks() - lastUpdateTime;
    Uint32 timeToWait = FRAME_MILLISECONDS - delta;
    if (timeToWait>0 && timeToWait < FRAME_MILLISECONDS) {
        SDL_Delay(timeToWait);
    }

    lastUpdateTime = SDL_GetTicks();

    registry->GetSystem<MovementSystem>().Update(delta/1000.f);

    registry->Update();
}

void Game::SpawnEntities() {

    registry->AddSystem<MovementSystem>();

    Entity tank = registry->CreateEntity();

    registry->AddComponent<Transform>(tank, glm::vec2(10,10));
    registry->AddComponent<RigidBody>(tank, glm::vec2(10, 10));

    registry->AddEntityToSystems(tank);
}


