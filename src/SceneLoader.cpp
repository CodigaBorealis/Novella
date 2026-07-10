#include "../Novella/Scene/Serialization/SceneLoader.hpp"
#include "../Novella/Scene/Scene.hpp"//clangd swears this file is unused, it IS used
#include "../Novella/Utils/FileSystem.hpp"
#include "../Novella/Scene/Parser/Lexer.hpp"
#include "../Novella/Scene/Parser/Parser.hpp"
#include "../Novella/Core/Engine.hpp"
#include <filesystem>
#include <stdexcept>
#include "../Novella/Scene/Serialization/ComponentBuilder.hpp"
#include "../Novella/Components/UI/Button.hpp"
#include "../Novella/Components/UI/Sprite.hpp"
#include "../Novella/Components/UI/DialogueBox.hpp"
#include "../Novella/Components/UI/Label.hpp"
#include "../Novella/Scripting/Interpreter/ScriptLoader.hpp"
#include "../Novella/Scripting/Parser/Script.hpp"
#include "../Novella/Scripting/Interpreter/Interpreter.hpp"

namespace Novella::NScene::Serialization{


    void Loader::load(NScript::Runtime::Context& context, const std::filesystem::path& file){

        std::string fileContents = Utils::Filesystem::getContentsFromFile(context.projectRoot / file);

        Parser::Lexer lexer(fileContents);

        Parser::Parser parser(lexer);

        Parser::SceneDefinition definition = parser.parse();

        build(context, definition);

    }

    void Loader::build(NScript::Runtime::Context& context, const Parser::SceneDefinition& scene){
                
        context.audio->clear();
        context.resources->clear();

        context.scene->clear();

        context.scene->createScene();
        
        loadResources(context, scene);

        context.audio->reloadResources();

        loadObjects(context, scene);

        context.interpreter->clear();

        loadScripts(context, scene);

    }

    void Loader::loadResources(NScript::Runtime::Context& context, const NScene::Parser::SceneDefinition& scene){

        for(const auto& resource : scene.resources){

            const std::filesystem::path relativePath = context.projectRoot / resource.path;

            if(resource.type == "texture"){

                context.resources->loadTexture(resource.name, relativePath);

            }else if (resource.type == "font"){

                context.resources->loadFont(resource.name, relativePath);
            
            }else if(resource.type == "music"){

                context.resources->loadAudio(resource.name, relativePath, "music");

            }else if(resource.type == "sfx"){

                context.resources->loadAudio(resource.name, relativePath, "sfx");

            }else{

                throw std::runtime_error("Invalid resource type '" + resource.type + "'");
            }
        }
    }

    void Loader::loadObjects(NScript::Runtime::Context& context, const NScene::Parser::SceneDefinition& scene){

        for(const auto& object : scene.objects){

            if(object.objectType == UI::Sprite::getStaticTypeID()){

                ComponentBuilder::buildSprite(context, object);

            }else if(object.objectType == UI::Button::getStaticTypeID()){

                ComponentBuilder::buildButton(context, object);

            }else if(object.objectType == UI::Label::getStaticTypeID()){

                ComponentBuilder::buildLabel(context, object);

            }
        }
    }

    void Loader::loadScripts(NScript::Runtime::Context& context, const NScene::Parser::SceneDefinition& scene){

        const std::filesystem::path root = context.projectRoot;

        for(const auto& definition : scene.scripts){

            std::filesystem::path relativePath = root / definition.path;
            
            auto script = NScript::Runtime::ScriptLoader::load(relativePath);

            context.interpreter->loadScript(script);
        }
    }
}
