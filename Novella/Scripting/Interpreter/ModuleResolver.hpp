#pragma once
#include "../Parser/Definition.hpp"
#include <variant>

namespace Novella::NScript::Parser{

    struct Script;
    

}

namespace Novella::NScript::Runtime{

    class ModuleResolver{

        using ImportDefinition = std::variant<Parser::ModuleImportDefinition, Parser::EngineImportDefinition, Parser::FunctionDefinition, Parser::ModuleImportDefinition>;

        public:

        ModuleResolver() = default;

        void resolveImports(Parser::Script& script);

        private:
        
        void resolveImport(const Parser::ImportDefinition& definition);

        void resolveModuleImport(const Parser::ModuleImportDefinition& module);
        void resolveEngineImport(const Parser::EngineImportDefinition& engineModule);
        
        void includeWindowModule();
        void includeAudioModule();
        void includeInputModule();
        void includeSceneModule();
        void includeAllModules();
    };

}