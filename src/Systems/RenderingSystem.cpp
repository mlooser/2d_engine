#include "RenderingSystem.h"

#include "../ECS/Registry.h"
#include <SDL2/SDL.h>

void RenderingSystem::Render(SDL_Renderer* renderer) {

    for (auto& entity : GetEntities()) {
        auto& transform = owner->GetCmponent<Transform>(entity);
        auto& sprite = owner->GetCmponent<Sprite>(entity);

        SDL_Rect srcRect = {
            static_cast<int>(transform.position.x),
            static_cast<int>(transform.position.y),
            sprite.sizeX, sprite.sizeY,
        };

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &srcRect);

    }
}
