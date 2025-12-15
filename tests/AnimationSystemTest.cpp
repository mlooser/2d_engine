#include <gtest/gtest.h>
#include "../src/Systems/AnimationSystem.h"
#include "../src/ECS/Registry.h"
#include "../src/Components/Sprite.h"
#include "../src/Components/SpriteAnimation.h"
#include "../src/Logger.h"

class AnimationSystemTest : public ::testing::Test {
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

TEST_F(AnimationSystemTest, CanAddEntityToSystems) {
    Entity entity = registry->CreateEntity();

    registry->AddComponent<Sprite>(entity, "test", 32, 32, 0, 0, 0);
    registry->AddComponent<SpriteAnimation>(entity, 2, 10, true);

    registry->AddSystem<AnimationSystem>();
    registry->AddEntityToSystems(entity);

    EXPECT_TRUE(true);
}

TEST_F(AnimationSystemTest, UpdateAdvancesFrameAfterEnoughTime) {
    Entity entity = registry->CreateEntity();

    registry->AddComponent<Sprite>(entity, "test", 32, 32, 0, 0, 0);
    registry->AddComponent<SpriteAnimation>(entity, 2, 10, true);

    registry->AddSystem<AnimationSystem>();

    registry->AddEntityToSystems(entity);

    EXPECT_EQ(registry->GetComponent<SpriteAnimation>(entity).currentFrame, 0);
    EXPECT_EQ(registry->GetComponent<Sprite>(entity).srcRect.x, 0);

    registry->GetSystem<AnimationSystem>().Update(0.05f);

    EXPECT_EQ(registry->GetComponent<SpriteAnimation>(entity).currentFrame, 0);
    EXPECT_EQ(registry->GetComponent<Sprite>(entity).srcRect.x, 0);

    registry->GetSystem<AnimationSystem>().Update(0.06f);

    EXPECT_EQ(registry->GetComponent<SpriteAnimation>(entity).currentFrame, 1);
    EXPECT_EQ(registry->GetComponent<Sprite>(entity).srcRect.x, 32); // Frame 1 * 32px width
}

TEST_F(AnimationSystemTest, UpdateLoopsBackToFirstFrame) {
    Entity entity = registry->CreateEntity();

    registry->AddComponent<Sprite>(entity, "test", 32, 32, 0, 0, 0);
    registry->AddComponent<SpriteAnimation>(entity, 2, 10, true);

    registry->AddSystem<AnimationSystem>();
    registry->AddEntityToSystems(entity);

    registry->GetSystem<AnimationSystem>().Update(0.11f);
    EXPECT_EQ(registry->GetComponent<SpriteAnimation>(entity).currentFrame, 1);

    registry->GetSystem<AnimationSystem>().Update(0.11f);
    EXPECT_EQ(registry->GetComponent<SpriteAnimation>(entity).currentFrame, 0);
    EXPECT_EQ(registry->GetComponent<Sprite>(entity).srcRect.x, 0);
}

TEST_F(AnimationSystemTest, UpdateStopsAtLastFrameWhenNotLooping) {
    Entity entity = registry->CreateEntity();

    registry->AddComponent<Sprite>(entity, "test", 32, 32, 0, 0, 0);
    registry->AddComponent<SpriteAnimation>(entity, 2, 10, false);

    registry->AddSystem<AnimationSystem>();
    registry->AddEntityToSystems(entity);

    registry->GetSystem<AnimationSystem>().Update(0.11f);
    EXPECT_EQ(registry->GetComponent<SpriteAnimation>(entity).currentFrame, 1);

    registry->GetSystem<AnimationSystem>().Update(0.11f);
    EXPECT_EQ(registry->GetComponent<SpriteAnimation>(entity).currentFrame, 1);
}