#pragma once
#include <string>
#include <variant>
#include <vector>
#include "Statement.hpp"
namespace Novella::NScript::Parser{

    struct ModuleImportDefinition{

        std::string source;
        std::string importedName;
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

    using ImportDefinition = std::variant<ModuleImportDefinition, EngineImportDefinition>;

}