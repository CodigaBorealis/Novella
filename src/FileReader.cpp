#include "../Novella/Utils/FileReader.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>


namespace Novella{

    std::string FileReader::getContentsFromFile(const std::filesystem::path& src){

        std::ifstream file(src);

        if(!file.is_open()) throw std::runtime_error("FileReader: could not open file " + src.string());

        std::ostringstream contents;

        contents << file.rdbuf();

        return contents.str();

    }

    bool FileReader::exists(const std::filesystem::path &file){

        return std::filesystem::exists(file);
    }

}