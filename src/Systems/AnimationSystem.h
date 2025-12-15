#pragma once
#include "../Components/SpriteAnimation.h"
#include "../Components/Sprite.h"
#include "../ECS/System.h"

class AnimationSystem : public System{
public:
    explicit AnimationSystem(Registry* owner) : System(owner) {
        RequireComponent<SpriteAnimation>();
        RequireComponent<Sprite>();
    }

    void Update(float deltaTime) override;
};

