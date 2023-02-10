#include <gtest/gtest.h>

#include "Fixtures/Files/FileEntitiesFixture.hpp"

namespace EngineTest
{
  TEST_F(FileEntitiesFixture, entities)
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
    EXPECT_EQ("Boxes", entities.at(0).name);
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

  TEST_F(FileEntitiesFixture, childs)
  {
    auto s = instance->GetSpecification();
    auto entities = s.entities;
    auto childs = entities.at(0).childs;
    EXPECT_EQ(2, childs.size());

    auto nochild = entities.at(1).childs;
    EXPECT_EQ(0, nochild.size());
  }

  TEST_F(FileEntitiesFixture, environment_lights)
  {
    auto s = instance->GetSpecification();
    auto env = s.environment;

    auto light = env->lights.front();
    EXPECT_EQ(12, light->size);
    EXPECT_EQ("Sun", light->type);

    auto transform = light->transform;
    EXPECT_FLOAT_EQ(0.0, transform->translation->x);
    EXPECT_FLOAT_EQ(10.0, transform->translation->y);
    EXPECT_FLOAT_EQ(0.0, transform->translation->z);
    EXPECT_FLOAT_EQ(0.0, transform->rotation->x);
    EXPECT_FLOAT_EQ(0.0, transform->rotation->y);
    EXPECT_FLOAT_EQ(0.0, transform->rotation->z);
    EXPECT_FLOAT_EQ(1.0, transform->rotation->w);
    EXPECT_FLOAT_EQ(1.0, transform->scale->x);
    EXPECT_FLOAT_EQ(1.0, transform->scale->y);
    EXPECT_FLOAT_EQ(1.0, transform->scale->z);

    auto direction = light->direction;
    EXPECT_FLOAT_EQ(0.0, direction.x);
    EXPECT_FLOAT_EQ(1.0, direction.y);
    EXPECT_FLOAT_EQ(0.0, direction.z);

    EXPECT_FLOAT_EQ(1.0, light->color.r);
    EXPECT_FLOAT_EQ(1.0, light->color.g);
    EXPECT_FLOAT_EQ(1.0, light->color.b);

    EXPECT_FLOAT_EQ(2.0, light->strength);
  }

  TEST_F(FileEntitiesFixture, cams)
  {
    const auto s = instance->GetSpecification();
    const auto cams = s.cameras;

    const auto cam = cams.front();

    EXPECT_EQ(2, cams.size());
    EXPECT_EQ("player", cam->name);
    EXPECT_FLOAT_EQ(10.0, cam->speed);
    EXPECT_FLOAT_EQ(0.05, cam->sensitivity);
    EXPECT_FLOAT_EQ(0.1, cam->nearPlane);
    EXPECT_FLOAT_EQ(1000.0, cam->farPlane);
    EXPECT_FLOAT_EQ(45.0, cam->fov);
  }
} // namespace EngineTest
