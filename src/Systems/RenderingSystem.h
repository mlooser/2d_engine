#pragma once

#include <SDL_render.h>

#include "../Components/Sprite.h"
#include "../Components/Transform.h"
#include "../ECS/System.h"

class AssetStore;

class RenderingSystem: public System {

    AssetStore* assets;

public:
    explicit RenderingSystem(
        Registry* owner,
        AssetStore* assetStore)
    : System(owner),
    assets(assetStore){
        RequireComponent<Transform>();
        RequireComponent<Sprite>();
    }

    void Render(SDL_Renderer* renderer);
};

