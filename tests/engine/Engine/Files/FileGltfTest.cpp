#include "Fixtures/Files/FileGltfFixture.hpp"

namespace EngineTest
{
  TEST_F(FileGltfFixture, checkNodes)
  {
    auto spec = instance->GetSpec();
    auto nodes = spec.nodes->GetItems();
    EXPECT_EQ(0, nodes.at(0).mesh);
    EXPECT_EQ("Cube", nodes.at(0).name);
  }

  TEST_F(FileGltfFixture, checkMeshes)
  {
    auto spec = instance->GetSpec();
    auto meshes = spec.meshes->GetItems();

    EXPECT_EQ("Cube", meshes[0].name);
    EXPECT_EQ(3, meshes[0].primitives.at(0).indices);
    EXPECT_EQ(0, meshes[0].primitives.at(0).material);
    EXPECT_EQ(0, meshes[0].primitives.at(0).attr.position);
    EXPECT_EQ(1, meshes[0].primitives.at(0).attr.normal);
    EXPECT_EQ(2, meshes[0].primitives.at(0).attr.textcoord_0);
  }

  TEST_F(FileGltfFixture, checkAccessors)
  {
    auto spec = instance->GetSpec();
    auto accessors = spec.accessors->GetItems();

    EXPECT_EQ(4, accessors.size());
    EXPECT_EQ(0, accessors.at(0).bufferView);
    EXPECT_EQ(5126, accessors.at(0).componentType);
    EXPECT_EQ("VEC3", accessors.at(0).type);
    EXPECT_EQ(-1, accessors.at(0).min->x);
    EXPECT_EQ(1, accessors.at(0).max->x);
  }

  TEST_F(FileGltfFixture, checkBufferViews)
  {
    auto spec = instance->GetSpec();
    auto buffers = spec.bufferViews->GetItems();

    EXPECT_EQ(4, buffers.size());
    EXPECT_EQ(0, buffers.at(0).buffer);
    EXPECT_EQ(288, buffers.at(0).byteLength);
    EXPECT_EQ(0, buffers.at(0).byteOffset);
  }

  TEST_F(FileGltfFixture, checkBuffers)
  {
    auto spec = instance->GetSpec();
    auto buffers = spec.buffers->GetItems();

    EXPECT_EQ(1, buffers.size());
    EXPECT_EQ(840, buffers.at(0).byteLength);
    EXPECT_EQ("box.bin", buffers.at(0).uri);
  }
}
