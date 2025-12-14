#pragma once
#include <string>
#include <SDL2/SDL.h>

struct Sprite {
    std::string textureName;
    int sizeX;
    int sizeY;
    SDL_Rect srcRect;

    explicit Sprite(
        const std::string &textureName = "",
        const int sizeX = 0,
        const int sizeY = 0,
        const int srcXPos = 0,
        const int srcYPos = 0)
        : textureName(textureName),
          sizeX(sizeX),
          sizeY(sizeY) {

        srcRect = {
            srcXPos,srcYPos,sizeX,sizeY
        };
    }
};
