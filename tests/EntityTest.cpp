#include <gtest/gtest.h>
#include "../src/ECS/Entity.h"

TEST(EntityTest, MultipleEntitiesHaveDifferentIds) {
    Entity entity1(1);
    Entity entity2(2);
    Entity entity3(3);

    EXPECT_EQ(entity1.GetId(), 1);
    EXPECT_EQ(entity2.GetId(), 2);
    EXPECT_EQ(entity3.GetId(), 3);
    EXPECT_NE(entity1.GetId(), entity2.GetId());
}
