#include "File.hpp"
#include <filesystem>
#include <stdexcept>
#include <string>
#include "stdio.h"

namespace mtEngine
{
    File::File(std::filesystem::path filename): filename(filename)
    {
        Load(filename);
    }

    void File::Load(const std::filesystem::path filename)
    {
        bool isExist = std::filesystem::exists(filename);
        if(!isExist) {
            const std::string msg = std::string(filename) + " not found or permission denied";
            throw std::invalid_argument(msg);
        }

        ext = filename.extension();
        ext.replace(0, 1, "");

        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            const std::string msg = std::string(filename) + " failed to open";
            throw std::invalid_argument(msg);
        }

        size = std::filesystem::file_size(filename);

        buf << file.rdbuf();

        if(isAscii()) {
            contentType = ContentType::ascii;
        } else {
            contentType = ContentType::binary;
        }
    }

    void File::Write(const std::filesystem::path filename, const std::string &buf)
    {
        std::fstream output_fstream;
        output_fstream.open(filename, std::ios_base::out);
        if (!output_fstream.is_open()) {
            const std::string msg = std::string(filename) + " failed to open";
            throw std::invalid_argument(msg);
        }

        output_fstream << buf;
    }

    const bool File::isAscii()
    {
        int c;
        while((c = buf.get()) != EOF && c <= 127);
        if(c == EOF) {
            return true;
        }

        return false;
    }
}
