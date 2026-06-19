#pragma once
#include "../Definition.hpp"
#include <variant>

namespace Novella::Syntax::NovellaScript{

    struct Script;

    class ModuleResolver{

        using ImportDefinition = std::variant<ModuleImportDefinition, EngineImportDefinition,FunctionDefinition, ModuleImportDefinition>;

        public:

        ModuleResolver() = default;

        void resolveImports(Script& script);

        private:
        
        void resolveImport(const ImportDefinition& definition);

        void resolveModuleImport(const ModuleImportDefinition& module);
        void resolveEngineImport(const EngineImportDefinition& engineModule);
        
        void includeWindowModule();
        void includeAudioModule();
        void includeInputModule();
        void includeSceneModule();
        void includeAllModules();
    };

}