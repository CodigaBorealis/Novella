#include "../Novella/IO/SceneLoader.hpp"
#include "../Novella/Scene/Scene.hpp"
#include "../Novella/IO/FileReader.hpp"
#include "../Novella/Syntax/Scene/Lexer.hpp"
#include "../Novella/Syntax/Scene/Parser.hpp"
#include "../Novella/Engine.hpp"
#include <stdexcept>
#include "../Novella/Components/Type.hpp"
#include <iostream>
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

        engine.scene().createScene();
        
        loadResources(engine, scene);

        std::cout << "Total loaded resources: " << engine.resources().size() << "\n";

        loadObjects(engine, scene);

        std::cout << "Total loaded objects:" << engine.scene().getCurrentScene().objects().size() << "\n";

        loadBinds(engine, scene);

        std::cout << "Total loaded binds: " << engine.input().size() << "\n";
    }

    void Loader::loadResources(Engine& engine, const Syntax::Scene::SceneDefinition& scene){

        for(const auto& resource : scene.resources){

            if(resource.type == "texture"){

                engine.resources().loadTexture(resource.name, resource.path);

            }else if (resource.type == "font"){

                engine.resources().loadFont(resource.name, resource.path);
            
            }else if(resource.type == "music"){

                engine.audio().createResource(resource.name, resource.path, Audio::AssetType::Music);

            }else if(resource.type == "sfx"){

                engine.audio().createResource(resource.name, resource.path, Audio::AssetType::SFX);

            }else{

                throw std::runtime_error("Invalid resource type '" + resource.type + "'");
            }
        }
    }

    void Loader::loadObjects(Engine& engine, const Syntax::Scene::SceneDefinition& scene){

        for(const auto& object : scene.objects){

            std::cout << "Object: " << object.objectType << " " << object.objectName << "\n";

            for(const auto& child : object.children){

                std::cout << "  Child: " << child.objectType << "\n";
            }

            if(object.objectType == Components::Type::Sprite){

                ComponentBuilder::buildSprite(engine, object);

            }else if(object.objectType == Components::Type::Button){

                ComponentBuilder::buildButton(engine, object);

            }else if(object.objectType == Components::Type::Label){

                ComponentBuilder::buildLabel(engine, object);
            } 
        }
    }

    void Loader::loadBinds(Engine& engine, const Syntax::Scene::SceneDefinition& scene){

        for(const auto& input : scene.inputs){

            InputBuilder::buildInput(engine, input);

        }
    }
}