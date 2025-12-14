#include "RenderingSystem.h"

#include "../ECS/Registry.h"
#include "../AssetStore/AssetStore.h"
#include <SDL2/SDL.h>

void RenderingSystem::Render(SDL_Renderer* renderer) {

    for (auto& entity : GetEntities()) {
        auto& transform = owner->GetComponent<Transform>(entity);
        auto& sprite = owner->GetComponent<Sprite>(entity);

        auto* texture =  assets->GetTexture(sprite.textureName);

        SDL_Rect srcRect = sprite.srcRect;

        SDL_Rect dstRect = {
            static_cast<int>(transform.position.x),
            static_cast<int>(transform.position.y),
            static_cast<int>(sprite.sizeX * transform.scale.x),
            static_cast<int>(sprite.sizeY * transform.scale.y)
        };

        SDL_RenderCopyEx(
            renderer,
            texture,
            &srcRect,
            &dstRect,
            transform.rotation,
            nullptr,
            SDL_FLIP_NONE);

    }
}
