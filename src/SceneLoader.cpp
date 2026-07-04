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

namespace Novella::NScene::Serialization{

    void Loader::load(Engine &engine, const std::filesystem::path& file){

        std::string fileContents = Utils::Filesystem::getContentsFromFile(engine.projectRoot() / file);

        Parser::Lexer lexer(fileContents);

        Parser::Parser parser(lexer);

        Parser::SceneDefinition definition = parser.parse();

        build(engine, definition);

    }

    void Loader::build(Engine& engine, const Parser::SceneDefinition& scene){
                
        engine.audio().clear();
        //engine.input().clear();
        engine.resources().clear();

        engine.scene().clear();

        engine.scene().createScene();
        
        loadResources(engine, scene);

        engine.audio().reloadResources();

        loadObjects(engine, scene);

        //engine.script().clear();

        loadScripts(engine, scene);

    }

    void Loader::loadResources(Engine& engine, const Parser::SceneDefinition& scene){

        for(const auto& resource : scene.resources){

            const std::filesystem::path relativePath = engine.projectRoot() / resource.path;

            if(resource.type == "texture"){

                engine.resources().loadTexture(resource.name, relativePath);

            }else if (resource.type == "font"){

                engine.resources().loadFont(resource.name, relativePath);
            
            }else if(resource.type == "music"){

                engine.resources().loadAudio(resource.name, relativePath, "music");

            }else if(resource.type == "sfx"){

                engine.resources().loadAudio(resource.name, relativePath, "sfx");

            }else{

                throw std::runtime_error("Invalid resource type '" + resource.type + "'");
            }
        }
    }

    void Loader::loadObjects(Engine& engine, const Parser::SceneDefinition& scene){

        for(const auto& object : scene.objects){

            if(object.objectType == UI::Sprite::getStaticTypeID()){

                ComponentBuilder::buildSprite(engine, object);

            }else if(object.objectType == UI::Button::getStaticTypeID()){

                ComponentBuilder::buildButton(engine, object);

            }else if(object.objectType == UI::Label::getStaticTypeID()){

                ComponentBuilder::buildLabel(engine, object);

            }
        }
    }

    void Loader::loadScripts(Engine& engine, const Parser::SceneDefinition& scene){

        const std::filesystem::path root = engine.projectRoot();

        for(const auto& definition : scene.scripts){

            std::filesystem::path relativePath = root / definition.path;
            
            auto script = NScript::Runtime::ScriptLoader::load(relativePath);

            engine.script().loadScript(script);
        }
    }
}