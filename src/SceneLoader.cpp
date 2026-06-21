#include "../Novella/Scene/Serialization/SceneLoader.hpp"
#include "../Novella/Scene/Scene.hpp"//clangd swears this file is unused, it IS used
#include "../Novella/Utils/FileReader.hpp"
#include "../Novella/Scene/Parser/Lexer.hpp"
#include "../Novella/Scene/Parser/Parser.hpp"
#include "../Novella/Core/Engine.hpp"
#include <stdexcept>
#include "../Novella/Scene/Serialization/ComponentBuilder.hpp"
#include "../Novella/Components/UI/Button.hpp"
#include "../Novella/Components/UI/Sprite.hpp"
#include "../Novella/Components/UI/DialogueBox.hpp"
#include "../Novella/Components/UI/Label.hpp"

namespace Novella::NScene::Serialization{

    void Loader::load(Engine &engine, const std::filesystem::path& file){

        std::string fileContents = FileReader::getContentsFromFile(file);

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

            if(resource.type == "texture"){

                engine.resources().loadTexture(resource.name, resource.path);

            }else if (resource.type == "font"){

                engine.resources().loadFont(resource.name, resource.path);
            
            }else if(resource.type == "music"){

                engine.resources().loadAudio(resource.name, resource.path, "music");

            }else if(resource.type == "sfx"){

                engine.resources().loadAudio(resource.name, resource.path, "sfx");

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

        for(const auto& script : scene.scripts){

            //engine.script().loadScript(script);
        }
    }
}