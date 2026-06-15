#include "../Novella/IO/SceneLoader.hpp"
#include "../Novella/Scene/Scene.hpp"//clangd swears this file is unused, it IS used
#include "../Novella/IO/FileReader.hpp"
#include "../Novella/Syntax/Scene/Lexer.hpp"
#include "../Novella/Syntax/Scene/Parser.hpp"
#include "../Novella/Engine.hpp"
#include <stdexcept>
#include "../Novella/Components/Type.hpp"
#include "../Novella/IO/ComponentBuilder.hpp"
#include "../Novella/IO/InputBuilder.hpp"
namespace Novella::SceneLoader{

    void Loader::load(Engine &engine, const std::filesystem::path& file){

        std::string fileContents = IO::FileReader::getContentsFromFile(file);

        Syntax::Scene::Lexer lexer(fileContents);

        Syntax::Scene::Parser parser(lexer);

        Syntax::Scene::SceneDefinition definition = parser.parse();

        build(engine, definition);

    }

    void Loader::build(Engine& engine, const Syntax::Scene::SceneDefinition& scene){
                
        engine.audio().clear();
        engine.input().clear();
        engine.resources().clear();

        engine.scene().clear();

        engine.scene().createScene();
        
        loadResources(engine, scene);

        engine.audio().reloadResources();

        loadObjects(engine, scene);

        loadBinds(engine, scene);

    }

    void Loader::loadResources(Engine& engine, const Syntax::Scene::SceneDefinition& scene){

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

    void Loader::loadObjects(Engine& engine, const Syntax::Scene::SceneDefinition& scene){

        for(const auto& object : scene.objects){

            if(object.objectType == Components::Type::Sprite){

                ComponentBuilder::buildSprite(engine, object);

            }else if(object.objectType == Components::Type::Button){

                ComponentBuilder::buildButton(engine, object);

            }else if(object.objectType == Components::Type::Label){

                ComponentBuilder::buildLabel(engine, object);

            }else{
                
                throw std::runtime_error("Invalid component type '" + object.objectType + "'");

            }
        }
    }

    void Loader::loadBinds(Engine& engine, const Syntax::Scene::SceneDefinition& scene){

        for(const auto& input : scene.inputs){

            InputBuilder::buildInput(engine, input);

        }
    }
}