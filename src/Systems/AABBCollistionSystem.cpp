//
// Created by Marcin Lusa on 16/12/2025.
//

#include "AABBCollistionSystem.h"
#include "../ECS/Registry.h"

void AABBCollisionSystem::Update(float deltaTime) {
    (void)deltaTime;

    const auto& entities = GetEntities();

    // Check each pair of entities for collision
    for (size_t i = 0; i < entities.size(); i++) {
        Entity a = entities[i];
        const auto& aTransform = owner->GetComponent<Transform>(a);
        const auto& aCollider = owner->GetComponent<RectCollider>(a);

        for (size_t j = i + 1; j < entities.size(); j++) {
            Entity b = entities[j];
            const auto& bTransform = owner->GetComponent<Transform>(b);
            const auto& bCollider = owner->GetComponent<RectCollider>(b);

            // Calculate AABB bounds (position is center)
            float aLeft = aTransform.position.x - (aCollider.sizeX / 2.0f);
            float aRight = aTransform.position.x + (aCollider.sizeX / 2.0f);
            float aTop = aTransform.position.y - (aCollider.sizeY / 2.0f);
            float aBottom = aTransform.position.y + (aCollider.sizeY / 2.0f);

            float bLeft = bTransform.position.x - (bCollider.sizeX / 2.0f);
            float bRight = bTransform.position.x + (bCollider.sizeX / 2.0f);
            float bTop = bTransform.position.y - (bCollider.sizeY / 2.0f);
            float bBottom = bTransform.position.y + (bCollider.sizeY / 2.0f);

            // AABB collision check
            if (aLeft < bRight && aRight > bLeft &&
                aTop < bBottom && aBottom > bTop) {
                owner->GetLogger().Info("Collision detected between entity " +
                                       std::to_string(a.GetId()) + " and entity " +
                                       std::to_string(b.GetId()));
            }
        }
    }
}
