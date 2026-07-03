#include "../Novella/Utils/FileSystem.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

#ifdef __linux__
#include <pwd.h>
#include <unistd.h>
#endif

namespace Novella::Utils{

    std::filesystem::path Filesystem::getRelativePath(const std::filesystem::path &path){

        #ifdef WIN32
        const char* home = std::getenv("USERPROFILE");

        if(!home) throw std::runtime_error("Could not determine home directory");

        return  std::filesystem::path(home) / path;
        #elif __linux__

        if(const char* home = std::getenv("HOME")) return std::filesystem::path(home) / path;

        struct passwd* pw = getpwuid(getuid());

        if(!pw) throw std::runtime_error("Could not determine home directory");

        const std::filesystem::path home = pw->pw_dir;

        return home / path;

        #else

        throw std::runtime_error("Unsupported platform");

        #endif

    }

    std::string Filesystem::getContentsFromFile(const std::filesystem::path& src){

        std::ifstream file(src);

        if(!file.is_open()) throw std::runtime_error("FileReader: could not open file " + src.string());

        std::ostringstream contents;

        contents << file.rdbuf();

        return contents.str();

    }

    bool Filesystem::exists(const std::filesystem::path &file){

        return std::filesystem::exists(file);
    }

    std::filesystem::path Filesystem::findProjectFile(const std::filesystem::path& relativePath){

        auto dir = std::filesystem::current_path();

        while(true){

            auto candidate = dir / relativePath;

            if(std::filesystem::exists(candidate)) return candidate;

            if(dir == dir.root_path()) throw std::runtime_error("Could not find " + relativePath.string());

            dir = dir.parent_path();
        }
    }
}