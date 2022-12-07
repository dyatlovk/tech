#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>

namespace mtEngine
{
  class File
  {
  public:
    struct Path;

  public:
    File() = default;
    File(std::filesystem::path filename);

    enum ContentType
    {
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

    const bool isWorkReady() { return isReady; }

    const static Path CreatePathInfo(const std::string &path);

  public:
    struct Path {
      std::string fileName;
      std::string ext;
      std::string fullName;
    };

  private:
    const bool isAscii();

  private:
    std::filesystem::path filename;
    std::string ext;
    ContentType contentType;
    std::stringstream buf;
    int size;
    bool isReady;

    private:
      const static std::string FindPathExtension(const std::string &path);
      const static std::string FindFileName(const std::string &path);
  };
} // namespace mtEngine
