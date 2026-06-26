#include "../Novella/Project/Project.hpp"
#include "../Novella/Project/Lexer.hpp"
#include "../Novella/Project/Parser.hpp"
#include "../Novella/Utils/FileReader.hpp"
#include <stdexcept>
#include <iostream>

namespace Novella::Project{

    EngineConfig load(const std::filesystem::path& src){

        if(!FileReader::exists(src)) throw std::runtime_error("Engine configuration file not found: " + src.string()); 

        std::string contents = FileReader::getContentsFromFile(src);

        Lexer lexer{contents};

        Parser parser{lexer};

        return parser.parse();
    }

}