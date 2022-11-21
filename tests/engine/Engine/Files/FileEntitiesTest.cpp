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
    EXPECT_FLOAT_EQ(1.0, transform->translation->x);
    EXPECT_FLOAT_EQ(5.0, transform->translation->y);
    EXPECT_FLOAT_EQ(2.0, transform->translation->z);

    EXPECT_FLOAT_EQ(0.5, transform->rotation->x);
    EXPECT_FLOAT_EQ(0.89, transform->rotation->y);
    EXPECT_FLOAT_EQ(0.1, transform->rotation->z);
    EXPECT_FLOAT_EQ(1.0, transform->rotation->w);

    EXPECT_FLOAT_EQ(1.0, transform->scale->x);
    EXPECT_FLOAT_EQ(1.0, transform->scale->y);
    EXPECT_FLOAT_EQ(1.0, transform->scale->z);
  }
} // namespace EngineTest
