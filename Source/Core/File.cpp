#include "File.h"
#include <fstream>
#include <cstdint>

std::string FileRead(const char* const filePath)
{
    std::ifstream in(filePath, std::ios::in | std::ios::binary);
    if (!in)
    {
        throw std::exception("Failed to open file.");
    }

    // Get the file size
    in.seekg(0, std::ios::end);
    const auto size = static_cast<uint32_t>(in.tellg());
    in.seekg(0, std::ios::beg);

    std::string contents;
    contents.resize(size);
    in.read(&contents[0], size);
    return contents;
}