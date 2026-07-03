#include "../Novella/Scripting/Interpreter/ScriptLoader.hpp"
#include "../Novella/Scripting/Parser/Script.hpp"
#include "../Novella/Scripting/Parser/Parser.hpp"
#include "../Novella/Scripting/Parser/Lexer.hpp"
#include "../Novella/Utils/FileSystem.hpp"
#include <stdexcept>

namespace Novella::NScript::Runtime{

    Parser::Script ScriptLoader::load(const std::filesystem::path& source){

        const std::string extension = source.extension().string();

        if(extension != ".nvs") throw std::runtime_error("'" + source.string() + "' is not a novellaScript file");

        std::string scriptContents = Utils::Filesystem::getContentsFromFile(source);

        Parser::Lexer lexer(scriptContents);

        Parser::Parser parser(lexer);
        
        return parser.parse();
    }

}