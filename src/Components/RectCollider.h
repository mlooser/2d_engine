#pragma once
#include <SDL_stdinc.h>

#include "glm/fwd.hpp"

struct RectCollider {
    Uint32 sizeX;
    Uint32 sizeY;

    RectCollider(Uint32 x, Uint32 y)
    : sizeX(x), sizeY(y) {}
};
