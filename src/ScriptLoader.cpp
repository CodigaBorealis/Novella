#include "../Novella/Syntax/NovellaScript/Interpreter/ScriptLoader.hpp"
#include "../Novella/Syntax/NovellaScript/Script.hpp"
#include "../Novella/IO/FileReader.hpp"
#include <stdexcept>

namespace Novella::Syntax::NovellaScript{

    Script ScriptLoader::load(const std::filesystem::path& source){

        if(source.extension().string() != "nvs") throw std::runtime_error("'" + source.string() + "' is not a novellaScript file");

        std::string scriptContents = IO::FileReader::getContentsFromFile(source);

        Lexer lexer(scriptContents);

        Parser parser(lexer);
        
        return parser.parse();
    }

}