#include "../Novella/Syntax/NovellaScript/Interpreter/ModuleResolver.hpp"
#include "../Novella/Syntax/NovellaScript/Script.hpp"

namespace Novella::Syntax::NovellaScript{

    void ModuleResolver::resolveImports(Script& script){

        for(const auto& definition : script.definitions){

            if(std::holds_alternative<ModuleImportDefinition>(definition)){

                auto& moduleImport = std::get<ModuleImportDefinition>(definition);

                resolveModuleImport(moduleImport);

            }else if(std::holds_alternative<EngineImportDefinition>(definition)){

                auto& engineImport = std::get<EngineImportDefinition>(definition);

                resolveEngineImport(engineImport);
            }
        }
    }

    void ModuleResolver::resolveModuleImport(const ModuleImportDefinition& module){

        std::string src = module.source;

        //if(!IO::FileReader::exists(src)) throw std::runtime_error("Could not find module '" + module.alias + "' at the provided path '" + module.source + "'");

        //loadedModules[module.importedName] = getModule(module);

    }

    void ModuleResolver::resolveEngineImport(const EngineImportDefinition& engineModule){

        switch(engineModule.include){

            case EngineImportDefinition::Handle::Window:

                includeWindowModule();

                break;

            case EngineImportDefinition::Handle::Audio: 
            
                includeAudioModule();

                break;

            case EngineImportDefinition::Handle::Input: 
            
                includeInputModule();

                break;

            case EngineImportDefinition::Handle::Scene: 
            
                includeSceneModule();

                break;

            case EngineImportDefinition::Handle::Novella: 
            
                includeAllModules();

                break;


            //Include the individual free functions of each .hpp module
        }

    }

    void ModuleResolver::includeWindowModule(){


    }

    void ModuleResolver::includeAudioModule(){


    }

    void ModuleResolver::includeInputModule(){


    }

    void ModuleResolver::includeSceneModule(){


    }

    void ModuleResolver::includeAllModules(){


    }
}