#pragma once

#include <glm/glm.hpp>

struct RigidBody {
    glm::vec2 velocity;

    explicit RigidBody(const glm::vec2 velocity = glm::vec2(0, 0))
    : velocity(velocity) {}
};
