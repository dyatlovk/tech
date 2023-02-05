#include "Scenes/World/Client/Communication.hpp"

#include <gtest/gtest.h>

#include "Fixtures/ClientFixture.hpp"
#include "third_party/json/json.hpp"

namespace WorldTest
{
  using json = nlohmann::json;
  TEST_F(ClientTest, deserialize)
  {
    json j;
    const auto isValid = j.accept(_str.c_str());
    EXPECT_TRUE(isValid);

    auto parsed = j.parse(_str.c_str());
    const auto st = Game::Client::MakeScene(&parsed);

    EXPECT_EQ(1, st->entities.size());
    EXPECT_EQ("box", st->entities.at(0)->name);
    EXPECT_EQ(5.0, st->entities.at(0)->transform->translate->x);
    EXPECT_EQ(1.0, st->entities.at(0)->transform->translate->y);
    EXPECT_EQ(2.0, st->entities.at(0)->transform->translate->z);

    EXPECT_EQ("Sun", st->environment->lights.at(0)->type);
    EXPECT_EQ(12, st->environment->lights.at(0)->size);
    EXPECT_EQ(1.0, st->environment->lights.at(0)->color->x);
    EXPECT_EQ(1.0, st->environment->lights.at(0)->color->y);
    EXPECT_EQ(1.0, st->environment->lights.at(0)->color->z);
    EXPECT_EQ(2.0, st->environment->lights.at(0)->strength);
  }

  TEST_F(ClientTest, MakeObject)
  {
    json j;
    const auto isValid = j.accept(_str_object_info.c_str());
    EXPECT_TRUE(isValid);

    auto parsed = j.parse(_str_object_info.c_str());
    const auto st = Game::Client::MakeObject(&parsed);

    EXPECT_EQ("build", st->entity.name);
    EXPECT_EQ(15, st->entity.transform->translate->x);
    EXPECT_EQ(1, st->entity.transform->translate->y);
    EXPECT_EQ(2, st->entity.transform->translate->z);

    EXPECT_EQ(1, st->entity.transform->rotate->x);
    EXPECT_EQ(2, st->entity.transform->rotate->y);
    EXPECT_EQ(3, st->entity.transform->rotate->z);
    EXPECT_EQ(1, st->entity.transform->rotate->w);

    EXPECT_EQ(1, st->entity.transform->scale->x);
    EXPECT_EQ(1, st->entity.transform->scale->y);
    EXPECT_EQ(1, st->entity.transform->scale->z);
  }
} // namespace WorldTest
