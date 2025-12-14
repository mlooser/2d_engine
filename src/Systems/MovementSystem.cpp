//
// Created by Marcin Lusa on 13/12/2025.
//

#include "MovementSystem.h"

#include "../ECS/Registry.h"

void MovementSystem::Update(float deltaTime) {
    System::Update(deltaTime);

    for (auto& entity : GetEntities()) {
        auto& transform = owner->GetCmponent<Transform>(entity);
        auto& rigidBody = owner->GetCmponent<RigidBody>(entity);

        transform.position += rigidBody.velocity * deltaTime;

        owner->GetLogger().Info(
            "New position is ("
            + std::to_string(transform.position.x)
            + ", " + std::to_string(transform.position.y) + ")");
    }
}
