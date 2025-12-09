#include "Game.h"

#include <iostream>

Game::Game() {
    if (SDL_Init(SDL_INIT_EVERYTHING)!=0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
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
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1,0);
    if (!renderer) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    isRunning = true;
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout<<"Game destroyed"<<std::endl;
}

void Game::Run() {
    while (isRunning) {
        ProcessEvents();
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
    SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}


