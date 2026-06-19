#pragma once
#include "ScriptFwd.hpp"
#include <vector>

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
            Scene,
            Novella
        };

        Handle include;
    };

    struct FunctionDefinition{

        std::string name;
        std::vector<std::string> parameters;
        std::vector<Statement> body;
    };

    struct ModuleDefinition{

        std::string name;
        std::vector<VariableStatement> variables;
        std::vector<FunctionDefinition> functions;
    };
}