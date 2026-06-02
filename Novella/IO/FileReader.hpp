#pragma once
#include <filesystem>
#include <string>

namespace Novella::IO{

    class FileReader{

        public:
        
        static std::string getContentsFromFile(const std::filesystem::path& src);

    };

}