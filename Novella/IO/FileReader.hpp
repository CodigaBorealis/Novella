#pragma once
#include <filesystem>
#include <string>

namespace Novella::IO{

    class FileReader{

        public:
        
        static std::string getContents(const std::filesystem::path& src);

        private:


    };

}