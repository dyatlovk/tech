#pragma once
#include <filesystem>
#include <gtest/gtest.h>
#include <memory>
#include <Files/File.hpp>
#include "third_party/json/json.hpp"

namespace EngineTest {
    class FileTest : public ::testing::Test
    {
    protected:
        FileTest() = default;
        ~FileTest() override = default;

        void SetUp() override
        {
            createTmpDir();
            instance = std::make_shared<mtEngine::File>();
        }

        void TearDown() override
        {
            ClearTmp();
        }

        void createTmpDir()
        {
            bool isExist = std::filesystem::exists(tmpDir);
            if(isExist) return;

            std::filesystem::create_directory(tmpDir);
        }

        void ClearTmp()
        {
             bool isExist = std::filesystem::exists(tmpDir);
             if(!isExist) return;

             std::filesystem::remove_all(tmpDir);
        }

        std::shared_ptr<mtEngine::File> instance;
        const std::string root = "../../..";
        const std::filesystem::path asciiFile = root + "/tests/engine/Fixtures/Files/file_ascii.txt";
        const std::filesystem::path binFile = root + "/tests/engine/Fixtures/Files/file_bin.bin";
        const std::filesystem::path pngFile = root + "/tests/engine/Fixtures/Files/image.png";
        const std::filesystem::path jsonFile = root + "/tests/engine/Fixtures/Files/json.json";
        const std::filesystem::path tmpDir = root + "/tests/engine/tmp";
    };
}
