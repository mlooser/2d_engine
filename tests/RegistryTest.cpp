#include <gtest/gtest.h>
#include "../src/ECS/Registry.h"
#include "../src/ECS/Entity.h"
#include "../src/Logger.h"

// Test System class
struct TestSystem : public System {
    int value;
    explicit TestSystem(Registry* owner, int val = 0) : System(owner), value(val) {}
};

// Test fixture for Registry tests
class RegistryTest : public ::testing::Test {
protected:
    void SetUp() override {
        logger = new Logger();
        registry = new Registry(logger);
    }

    void TearDown() override {
        delete registry;
        delete logger;
    }

    Logger* logger;
    Registry* registry;
};

TEST_F(RegistryTest, CreateMultipleEntitiesReturnsSequentialIds) {
    Entity entity1 = registry->CreateEntity();
    Entity entity2 = registry->CreateEntity();
    Entity entity3 = registry->CreateEntity();

    EXPECT_EQ(entity1.GetId(), 0);
    EXPECT_EQ(entity2.GetId(), 1);
    EXPECT_EQ(entity3.GetId(), 2);
}

TEST_F(RegistryTest, HasSystemReturnsFalseWhenSystemNotAdded) {
    EXPECT_FALSE(registry->HasSystem<TestSystem>());
}

TEST_F(RegistryTest, AddSystemAddsSystemToRegistry) {
    registry->AddSystem<TestSystem>();
    EXPECT_TRUE(registry->HasSystem<TestSystem>());
}

TEST_F(RegistryTest, GetSystemReturnsAddedSystem) {
    registry->AddSystem<TestSystem>(42);

    TestSystem& system = registry->GetSystem<TestSystem>();

    EXPECT_EQ(system.value, 42);
}

