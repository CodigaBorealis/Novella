#include "../Novella/Project/Project.hpp"
#include "../Novella/Project/Lexer.hpp"
#include "../Novella/Project/Parser.hpp"
#include "../Novella/Utils/FileSystem.hpp"
#include <stdexcept>

namespace Novella::Project{

    EngineConfig load(const std::filesystem::path& configFile){

        const std::filesystem::path relativePath = Utils::Filesystem::getRelativePath(configFile);

        if(!Utils::Filesystem::exists(relativePath)) throw std::runtime_error("Project root folder not found: " + relativePath.string()); 
        
        std::string contents = Utils::Filesystem::getContentsFromFile(relativePath);

        Lexer lexer{contents};

        Parser parser{lexer};

        return parser.parse();
    }

}