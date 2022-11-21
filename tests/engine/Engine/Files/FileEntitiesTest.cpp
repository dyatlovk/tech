#include <gtest/gtest.h>

#include "Fixtures/Files/FileEntitiesFixture.hpp"

namespace EngineTest
{
  TEST_F(FileEntitiesFixture, spec)
  {
    auto s = instance->GetSpecification();

    EXPECT_EQ("World", s.name);
    EXPECT_EQ("Kirill Dyatlov", s.author);
    EXPECT_EQ("Test game scene", s.description);
    EXPECT_EQ("1.0", s.version);

    auto entities = s.entities;
    EXPECT_EQ(2, entities.size());
    auto transform = entities.at(0).transform;
    EXPECT_EQ("/Game/models/boxes.gltf", entities.at(0).model);
    EXPECT_EQ(0, transform->translation->x);
    EXPECT_EQ(0, transform->translation->y);
    EXPECT_EQ(0, transform->translation->z);

    EXPECT_EQ(0, transform->rotation->x);
    EXPECT_EQ(0, transform->rotation->y);
    EXPECT_EQ(0, transform->rotation->z);
    EXPECT_EQ(1.0, transform->rotation->w);

    EXPECT_EQ(1.0, transform->scale->x);
    EXPECT_EQ(1.0, transform->scale->y);
    EXPECT_EQ(1.0, transform->scale->z);
  }
} // namespace EngineTest
