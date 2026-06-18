#pragma once
#include "ScriptFwd.hpp"

namespace Novella::Syntax::NovellaScript {
    
    struct ModuleImportDefinition{

        std::string source;
        std::string importedName;
        std::string alias;

    };

    struct EngineImportDefinition{

        enum class Handle : unsigned int{
            
            Window,
            Audio,
            Input,
            Scene
        };
    };

    struct FunctionDefinition{

        std::string name;
        std::vector<std::string> parameters;
        std::vector<Statement> body;
    };

    struct ModuleDefinition{

        std::string name;
        bool exported;
        std::vector<Statement> firstLoad;
        std::vector<FunctionDefinition> functions;
    };
}