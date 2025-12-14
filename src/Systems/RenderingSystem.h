#pragma once

#include <SDL_render.h>

#include "../Components/Sprite.h"
#include "../Components/Transform.h"
#include "../ECS/System.h"

class RenderingSystem: public System {

public:
    explicit RenderingSystem(
        Registry* owner)
    : System(owner){
        RequireComponent<Transform>();
        RequireComponent<Sprite>();
    }

    void Render(SDL_Renderer* renderer);
};

