#include "Fixtures/Resources/ResourcesManagerFixture.hpp"

namespace EngineTest
{
  TEST_F(ResourcesManagerTest, add)
  {
    instance->add("test", resourse);
    auto found = instance->find<ResourceTest>("test");
    EXPECT_EQ(resourse, found);
  }

  TEST_F(ResourcesManagerTest, getAll)
  {
    instance->add("test", resourse);
    auto all = instance->GetAll();
    EXPECT_EQ(1, all.size());
  }

  TEST_F(ResourcesManagerTest, replace)
  {
    instance->add("test", resourse);
    std::shared_ptr<ResourceTest> replaced = std::make_shared<ResourceTest>();
    replaced->checkFlag = 1;
    instance->replace("test", replaced);

    auto found = instance->find<ResourceTest>("test");
    EXPECT_EQ(1, found->checkFlag);
    EXPECT_EQ(0, resourse->checkFlag);
  }

  TEST_F(ResourcesManagerTest, remove)
  {
    instance->add("test", resourse);
    instance->remove("test");
    auto all = instance->GetAll();
    EXPECT_EQ(0, all.size());
  }

  TEST_F(ResourcesManagerTest, remove_not_found_cmd)
  {
    instance->add("test", resourse);
    instance->remove("test2");
    auto all = instance->GetAll();
    EXPECT_EQ(1, all.size());
  }
} // namespace EngineTest
