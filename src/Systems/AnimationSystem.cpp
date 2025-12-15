#include "AnimationSystem.h"
#include "../Components/Sprite.h"
#include "../ECS/Registry.h"
#include <iostream>

void AnimationSystem::Update(float deltaTime) {
    for (auto& entity : GetEntities()) {
        auto& animation = owner->GetComponent<SpriteAnimation>(entity);
        auto& sprite = owner->GetComponent<Sprite>(entity);

        animation.lastUpdate += deltaTime;

        if (animation.lastUpdate * animation.framesPerSecond >= 1.0) {
            animation.currentFrame++;

            if (animation.currentFrame >= animation.numFrames) {
                if (animation.loop) {
                    animation.currentFrame = 0;
                } else {
                    animation.currentFrame = animation.numFrames - 1;
                }
            }

            sprite.srcRect.x = animation.currentFrame * sprite.sizeX;

            animation.lastUpdate = 0.0;
        }
    }
}
