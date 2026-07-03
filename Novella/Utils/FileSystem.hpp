#pragma once
#include <string>
#include <filesystem>

namespace Novella::Utils{

    class Filesystem{
    
    public:

    static std::string getContentsFromFile(const std::filesystem::path& src);
    
    static std::filesystem::path findProjectFile(const std::filesystem::path& relativePath);

    static std::filesystem::path getRelativePath(const std::filesystem::path& path);

    static bool exists(const std::filesystem::path& src);

    };
}