#include <gtest/gtest.h>
#include "../src/ECS/Registry.h"
#include "../src/ECS/System.h"
#include "../src/ECS/Component.h"

// Test Component
struct TestComponent {
    int value;
    TestComponent(int v = 0) : value(v) {}
};

// Test System
class TestSystem : public System {};

TEST(AddEntityToSystemsTest, OnlyAddsEntitiesWithRequiredComponent) {
    Registry registry;

    // Create a system that requires TestComponent
    registry.AddSystem<TestSystem>();
    TestSystem& system = registry.GetSystem<TestSystem>();
    system.RequireComponent<TestComponent>();

    // Create two entities
    Entity entity1 = registry.CreateEntity();
    Entity entity2 = registry.CreateEntity();

    // Add TestComponent only to entity1
    registry.AddComponent<TestComponent>(entity1, 42);

    // Add entities to systems
    registry.AddEntityToSystems(entity1);
    registry.AddEntityToSystems(entity2);

    // Verify only entity1 is in the system
    const auto& entities = system.GetEntities();
    ASSERT_EQ(entities.size(), 1);
    EXPECT_EQ(entities[0].GetId(), entity1.GetId());
}
