#pragma once
#include "../Components/RectCollider.h"
#include "../Components/Transform.h"
#include "../ECS/System.h"

class AABBCollisionSystem : public System {
public:
    AABBCollisionSystem(Registry *owner) : System(owner) {
        RequireComponent<Transform>();
        RequireComponent<RectCollider>();
    }

    void Update(float deltaTime) override;
};
