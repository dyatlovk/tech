#include <gtest/gtest.h>

#include "Fixtures/Files/FileFixture.hpp"

namespace EngineTest
{
  TEST_F(FileTest, loadAscii)
  {
    instance->Load(asciiFile);
    auto content = instance->GetBuffer();
    EXPECT_EQ("text", content);
  }

  TEST_F(FileTest, fileNotFound)
  {
    EXPECT_THROW(instance->Load("not_found.txt"), std::invalid_argument);
  }

  TEST_F(FileTest, contentType)
  {
    instance->Load(asciiFile);
    auto type = instance->GetType();
    EXPECT_EQ(type, mtEngine::File::ascii);
  }

  TEST_F(FileTest, loadBin)
  {
    instance->Load(binFile);
    auto type = instance->GetType();
    auto content = instance->GetBuffer();
    EXPECT_EQ(type, mtEngine::File::binary);
  }

  TEST_F(FileTest, checkBinarySize)
  {
    instance->Load(binFile);
    auto size = instance->GetFileSize();
    EXPECT_EQ(840, size);
  }

  TEST_F(FileTest, checkAsciiSize)
  {
    instance->Load(asciiFile);
    auto size = instance->GetFileSize();
    EXPECT_EQ(4, size);
  }

  TEST_F(FileTest, writeFile)
  {
    const std::filesystem::path file = std::string(tmpDir) + "/file.txt";
    const std::string buf = "Hello";
    instance->Write(file, buf);

    instance->Load(file);
    EXPECT_EQ(buf, instance->GetBuffer());
    EXPECT_EQ(buf.size(), instance->GetFileSize());
    EXPECT_EQ("txt", instance->GetExt());
    EXPECT_EQ(mtEngine::File::ascii, instance->GetType());
  }

  TEST_F(FileTest, loadViaConstructor)
  {
    auto file = std::make_unique<mtEngine::File>(asciiFile);
    EXPECT_EQ("text", file->GetBuffer());
  }

  TEST_F(FileTest, loadPng)
  {
    instance->Load(pngFile);
    EXPECT_EQ(1967, instance->GetFileSize());
  }

  TEST_F(FileTest, isWorkReady)
  {
    instance->Load(asciiFile);
    auto isReady = instance->isWorkReady();
    EXPECT_TRUE(isReady);
  }
} // namespace EngineTest
