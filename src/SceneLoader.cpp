#include "../Novella/IO/SceneLoader.hpp"
#include "../Novella/Scene/Scene.hpp"
#include "../Novella/IO/FileReader.hpp"
#include "../Novella/Syntax/Scene/Lexer.hpp"
#include "../Novella/Syntax/Scene/Parser.hpp"
#include "../Novella/Attribute/Object.hpp"
#include "../Novella/Layout/Layout.hpp"
#include "../Novella/Engine.hpp"
#include <stdexcept>
#include "../Novella/Components/Background.hpp"

namespace Novella::IO{

    Scene SceneLoader::load(Engine &engine, const std::filesystem::path& file){

        std::string fileContents = FileReader::getContentsFromFile(file);

        Syntax::Scene::Lexer lexer(fileContents);

        Syntax::Scene::Parser parser(lexer);

        Syntax::Scene::SceneDefinition definition = parser.parse();

        return build(engine, definition);

    }

    Scene SceneLoader::build(Engine& engine, const Syntax::Scene::SceneDefinition& scene){

        engine.scene().createScene();

        for(const auto& resource : scene.resources){

            if(resource.type == "texture"){

                engine.resources().loadTexture(resource.name, resource.path);

            }else if (resource.type == "font"){

                engine.resources().loadFont(resource.name, resource.type);
            
            }else if(resource.type == "music"){

                engine.audio().createResource(resource.name, resource.path, Audio::AssetType::Music);

            }else if(resource.type == "sfx"){

                engine.audio().createResource(resource.name, resource.path, Audio::AssetType::SFX);
            }
        }

        for(const auto& object : scene.objects){

                buildObject(engine, object);
            
        }
    }

    void SceneLoader::buildObject(Engine& engine, const Syntax::Scene::ObjectDefinition& object){

        if(object.objectType == "background"){

            engine.scene().addObject<Components::Background>(

                engine.resources().getTexture(getIdentifier(object, "texture")),

                getLayout(object),

                getRenderLayer(object)

            );
        }
    }

    const Syntax::Scene::Property* SceneLoader::findProperty(const Syntax::Scene::ObjectDefinition& object, const std::string& name){

        for(const auto& property : object.properties){

            if(property.name == name) return &property;
        }

        return nullptr;
    }

    std::string SceneLoader::getIdentifier(const Syntax::Scene::ObjectDefinition& object, const std::string& name){

        auto* identifier = findProperty(object, name);

        if(!identifier) throw std::runtime_error("Missing property: '" + name +"' for '" + object.objectName + "'");

        return identifier->value.StringValue;
    }

    int SceneLoader::getRenderLayer(const Syntax::Scene::ObjectDefinition& object){

        auto* renderLayer = findProperty(object, "renderLayer");

        if(renderLayer == nullptr) throw std::runtime_error("Missing property 'renderLayer' for '" + object.objectName + "'");

        return  renderLayer->value.numberValue;
    }

    Anchor SceneLoader::getAnchor(const Syntax::Scene::Property* anchorProperty){

        if(anchorProperty->value.StringValue == "TopLeft"){

            return Anchor::TopLeft;

        } else if(anchorProperty->value.StringValue == "TopCenter"){

            return Anchor::TopCenter;

        }else if(anchorProperty->value.StringValue == "TopRight"){

            return Anchor::TopRight;

        }else if(anchorProperty->value.StringValue == "CenterLeft"){

            return Anchor::CenterLeft;

        }else if(anchorProperty->value.StringValue == "Center"){

            return Anchor::Center;

        }else if(anchorProperty->value.StringValue == "CenterRight"){

            return Anchor::CenterRight;

        }else if(anchorProperty->value.StringValue == "BottomLeft"){

            return Anchor::BottomLeft;

        }else if(anchorProperty->value.StringValue == "BottomCenter"){

            return Anchor::BottomCenter;

        }else if(anchorProperty->value.StringValue == "BottomRight"){

            return Anchor::BottomCenter;
        }

        throw std::runtime_error("Invalid value for property anchor '" + anchorProperty->value.StringValue +"'");
    }

    const Syntax::Scene::ObjectDefinition* SceneLoader::findChild(const Syntax::Scene::ObjectDefinition& object, const std::string& type){

        for(const auto& child : object.children){

            if(child.objectType == type) return &child;
            
        }

        return nullptr;
    }

    Layout SceneLoader::getLayout(const Syntax::Scene::ObjectDefinition& object){

        Layout layout{};

        auto* layoutNode = findChild(object, "layout");

        if(!layoutNode) return layout;

        if(auto* anchor = findProperty(*layoutNode, "anchor")){

            layout.anchor = getAnchor(anchor);
        }

        auto* widthMode = findChild(object, "widthMode");
        
        return layout;
    }
}