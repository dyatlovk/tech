#pragma once

#include <ostream>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace mtEngine
{
    class File
    {
        public:
            File() = default;
            File(std::filesystem::path filename);

            enum ContentType {
                binary = 1,
                ascii = 2,
            };

            void Load(const std::filesystem::path filename);

            void Write(const std::filesystem::path filename, const std::string &buf);

            const std::string getFileName() { return filename; }

            const std::string GetBuffer() { return buf.str(); }

            const std::string GetExt() { return ext; }

            const ContentType GetType() { return contentType; }

            const int GetFileSize() { return size; }
        private:
            const bool isAscii();
        private:
            std::filesystem::path filename;
            std::string ext;
            ContentType contentType;
            std::stringstream buf;
            int size;
    };
} // namespace mtEngine
