#include "../Novella/Scripting/Interpreter/ModuleResolver.hpp"
#include "../Novella/Scripting/Parser/Script.hpp"

namespace Novella::NScript::Runtime{

    void ModuleResolver::resolveImports(Parser::Script& script){

        for(const auto& definition : script.definitions){

            if(std::holds_alternative<Parser::ModuleImportDefinition>(definition)){

                auto& moduleImport = std::get<Parser::ModuleImportDefinition>(definition);

                resolveModuleImport(moduleImport);

            }else if(std::holds_alternative<Parser::EngineImportDefinition>(definition)){

                auto& engineImport = std::get<Parser::EngineImportDefinition>(definition);

                resolveEngineImport(engineImport);
            }
        }
    }

    void ModuleResolver::resolveModuleImport(const Parser::ModuleImportDefinition& module){

        std::string src = module.source;

        //if(!IO::FileReader::exists(src)) throw std::runtime_error("Could not find module '" + module.alias + "' at the provided path '" + module.source + "'");

        //loadedModules[module.importedName] = getModule(module);

    }

    void ModuleResolver::resolveEngineImport(const Parser::EngineImportDefinition& engineModule){

        switch(engineModule.include){

            case Parser::EngineImportDefinition::Handle::Window:

                includeWindowModule();

                break;

            case Parser::EngineImportDefinition::Handle::Audio: 
            
                includeAudioModule();

                break;

            case Parser::EngineImportDefinition::Handle::Input: 
            
                includeInputModule();

                break;

            case Parser::EngineImportDefinition::Handle::Scene: 
            
                includeSceneModule();

                break;

            case Parser::EngineImportDefinition::Handle::Novella: 
            
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