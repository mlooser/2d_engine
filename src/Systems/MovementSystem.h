#pragma once
#include "../Components/RigidBody.h"
#include "../Components/Transform.h"
#include "../ECS/System.h"


class MovementSystem : public System {

public:
    explicit MovementSystem(Registry* owner) : System(owner) {
        RequireComponent<Transform>();
        RequireComponent<RigidBody>();
    }

    void Update(float deltaTime) override;
};

