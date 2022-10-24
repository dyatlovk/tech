#include "Files/FileGltf.hpp"
#include "Fixtures/Files/FileGltfFixture.hpp"

namespace EngineTest
{
  TEST_F(FileGltfFixture, scenes)
  {
    auto spec = instance->GetSpecification();
    auto scenes = spec.scenes->GetSection();

    EXPECT_EQ("Scene", *scenes.name);
    EXPECT_EQ(0, scenes.nodes.at(0));
  }

  TEST_F(FileGltfFixture, checkNodes)
  {
    auto spec = instance->GetSpecification();
    auto nodes = spec.nodes->GetItems();

    EXPECT_EQ(0, *nodes.at(0).mesh);
    EXPECT_EQ("Cube", *nodes.at(0).name);
    EXPECT_EQ(0, nodes.at(0).rotation->x);
    EXPECT_EQ(0.3826834261417389, nodes.at(0).rotation->y);
    EXPECT_EQ(0, nodes.at(0).rotation->z);
    EXPECT_EQ(0.9238795638084412, nodes.at(0).rotation->w);
    EXPECT_EQ(0, nodes.at(0).translation->x);
    EXPECT_EQ(0, nodes.at(0).translation->y);
    EXPECT_EQ(-4.179202556610107, nodes.at(0).translation->z);
    EXPECT_EQ(1, nodes.at(0).scale->x);
    EXPECT_EQ(1, nodes.at(0).scale->y);
    EXPECT_EQ(1, nodes.at(0).scale->z);
    EXPECT_TRUE(nodes.at(0).children == nullptr);
  }

  TEST_F(FileGltfFixture, checkMeshes)
  {
    auto spec = instance->GetSpecification();
    auto meshes = spec.meshes->GetItems();

    EXPECT_EQ("Cube", *meshes[0].name);
    EXPECT_TRUE(meshes.at(0).primitives.at(0).mode == nullptr);
    EXPECT_EQ(3, *meshes[0].primitives.at(0).indices);
    EXPECT_EQ(0, *meshes[0].primitives.at(0).material);
    EXPECT_EQ(0, meshes[0].primitives.at(0).attr.position);
    EXPECT_EQ(1, meshes[0].primitives.at(0).attr.normal);
    EXPECT_EQ(2, meshes[0].primitives.at(0).attr.textcoord_0);
  }

  TEST_F(FileGltfFixture, checkAccessors)
  {
    auto spec = instance->GetSpecification();
    auto accessors = spec.accessors->GetItems();

    EXPECT_EQ(4, accessors.size());
    EXPECT_EQ(0, *accessors.at(0).bufferView);
    EXPECT_EQ(mtEngine::Files::Accessors::AccessorsComponentTypes::FLOAT, accessors.at(0).componentType);
    EXPECT_EQ("VEC3", accessors.at(0).type);
    EXPECT_EQ(-1, accessors.at(0).min->at(0));
    EXPECT_EQ(1, accessors.at(0).max->at(0));
  }

  TEST_F(FileGltfFixture, checkBufferViews)
  {
    auto spec = instance->GetSpecification();
    auto buffers = spec.bufferViews->GetItems();

    EXPECT_EQ(4, buffers.size());
    EXPECT_EQ(0, buffers.at(0).buffer);
    EXPECT_EQ(288, buffers.at(0).byteLength);
    EXPECT_EQ(0, *buffers.at(0).byteOffset);
  }

  TEST_F(FileGltfFixture, checkBuffers)
  {
    auto spec = instance->GetSpecification();
    auto buffers = spec.buffers->GetItems();

    EXPECT_EQ(1, buffers.size());
    EXPECT_EQ(840, buffers.at(0).byteLength);
    EXPECT_EQ("box.bin", *buffers.at(0).uri);
    EXPECT_EQ("/", buffers.at(0).extras->path);
    EXPECT_TRUE(buffers.at(0).name == nullptr);
  }

  TEST_F(FileGltfFixture, checkAssets)
  {
    auto spec = instance->GetSpecification();
    auto assets = spec.assets->GetSection();

    EXPECT_EQ("2.0", assets.version);
    EXPECT_EQ("Khronos glTF Blender I/O v1.7.33", *assets.generator);
    EXPECT_TRUE(assets.copyright == nullptr);
  }

  TEST_F(FileGltfFixture, checkExtras)
  {
    auto spec = instance->GetSpecification();
    auto extras = spec.extras->GetSection();

    EXPECT_EQ("/Game/models", *extras.gameModelsRelativePath);
    EXPECT_EQ("/Game/textures", *extras.gameTexturesRelativePath);
  }
}
