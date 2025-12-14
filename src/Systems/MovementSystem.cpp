//
// Created by Marcin Lusa on 13/12/2025.
//

#include "MovementSystem.h"

#include "../ECS/Registry.h"

void MovementSystem::Update(float deltaTime) {
    System::Update(deltaTime);

    for (auto& entity : GetEntities()) {
        auto& transform = owner->GetComponent<Transform>(entity);
        auto& rigidBody = owner->GetComponent<RigidBody>(entity);

        transform.position += rigidBody.velocity * deltaTime;
    }
}
