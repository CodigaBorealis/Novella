#include "../Novella/Scene/SceneBuilder.hpp"
//#include "../Novella/Components/Character.hpp"
//#include "../../../Include/Moon/Components/Background.hpp"
//#include "../../../Include/Moon/Components/Button.hpp"
//#include "../../../Include/Moon/Components/DialogueBox.hpp"
//#include "../../../Include/Moon/Components/Label.hpp"
#include "../Novella/Input/Keyboard.hpp"
#include "../Novella/Input/Mouse.hpp"
#include <cstdint>
#include <memory>
#include <string>

namespace Novella{

    SceneBuilder::SceneBuilder(const Rendering::ResourceManager& resourceManager)
        :
        resourceManager(resourceManager)
        {
            initFactory();

        }

        void SceneBuilder::restoreKeybinds(Attribute::Interactable& component, const nlohmann::json& data){

            if(data.contains("keybinds")){

                for(const auto& bind : data["keybinds"]){

                    if(bind.contains("key") && bind.contains("action")){

                        component.addKeyboardBind(static_cast<Input::Keyboard::Key>(bind["key"]), {bind["action"], bind["args"], bind["target"]});

                    }

                }
            }
        }

        void SceneBuilder::restoreMouseBinds(Attribute::Clickable& component, const nlohmann::json& data){

            if(data.contains("mouseBinds")){

                for(const auto& bind : data["mouseBinds"]){
                    
                    if(bind.contains("button") && bind.contains("action")){

                        component.addMouseBind(static_cast<Input::Mouse::Button>(bind["button"]), {bind["action"], bind["args"], bind["target"]});

                    }
                }
            }

    }

        Scene& SceneBuilder::restoreBehaviour(Scene& scene, const nlohmann::json& data){

            const auto& objects = data["objects"];
            
            for(auto& objectData : objects){

                const auto& props = objectData["properties"];
                const std::string& id = props["id"];

                auto* object = scene.findObjectByID(id);

                if(!object) continue;

                if(auto* interactable = dynamic_cast<Attribute::Interactable*>(object)){

                    restoreKeybinds(*interactable, props);
                }

                if(auto* interactable = dynamic_cast<Attribute::Clickable*>(object)){

                    restoreMouseBinds(*interactable, props);
                }

            }

            return scene;
        }

        std::unique_ptr<Scene> SceneBuilder::build(const nlohmann::json& data){

            auto scene = std::make_unique<Scene>();

            for(auto& obj : data["objects"]){

                const auto& type = obj["type"];
                const auto& props = obj["properties"];

                auto instance = factory.create(type, props, resourceManager);

                scene->addObject(std::move(instance));
            }

            restoreBehaviour(*scene, data);

            return scene;

        }
        
        void SceneBuilder::initFactory(){

        /*This giant wall contains the information for the factory on how
        *to deserialize every component
        *it's ugly but i dont know where else to put this without
        *making myself lose even more sanity
        */
                /*
        //Builder
        factory.registerType("Character", makeBuilder<Components::Character>(

            [this](const nlohmann::json& data, const Rendering::ResourceManager& resourceManager){

            return std::make_unique<Components::Character>(

                getString(data, "id"),
                getTexture(data),
                getVector2i(data, "position"),
                getRenderLayer(data),
                getVector2i(data, "dimensions")

            );
        },//Post build functions
            [this](const auto& data, auto& obj){applyColorMask(data, obj);}
        ));


        factory.registerType("Background",makeBuilder<Components::Background>(

            [this](const nlohmann::json& data, const ResourceManager& resourceManager){

            return std::make_unique<Components::Background>(
                
                getSprite(data),
                getString(data, "id"),
                getRenderLayer(data)
            );
        },
            [this](const auto& data, auto& obj){applyColorMask(data, obj);}

        ));
        factory.registerType("Button", makeBuilder<Components::Button>(

            [this](const nlohmann::json& data, const ResourceManager& resourceManager){

            return std::make_unique<Components::Button>(

                getSprite(data),
                getString(data, "id"),
                getVector2D(data, "position"),
                getRenderLayer(data),
                getVector2D(data, "dimensions")

            );
        },
            [this](const auto& data, auto& obj){applyColorMask(data, obj);}

        ));

        factory.registerType("DialogueBox", makeBuilder<Components::DialogueBox>(

            [this](const nlohmann::json& data, const ResourceManager& resourceManager){

            return std::make_unique<Components::DialogueBox>(

                getSprite(data),
                getFont(data),
                getVector2D(data, "position"),
                getVector2D(data, "textOffset"),
                getString(data, "id"),
                getRenderLayer(data),
                getVector2D(data, "dimensions")

            );
        },

        [this](const auto& data, auto& obj){

            applyColorMask(data, obj);
            getDialogueController(data, obj);
        }
        
        ));

        factory.registerType("Label", makeBuilder<Components::Label>(
            
            [this](const nlohmann::json& data, const ResourceManager& resourceManager){

            return std::make_unique<Components::Label>(

                getString(data, "text"),
                getFont(data),
                data.at("fontSize"),
                getVector2D(data, "position"),
                getString(data, "id"),
                getRenderLayer(data)
            );
        },

        [this](const auto& data, auto& obj){applyColorMask(data, obj);}

        ));
    }
*/
    }

    int SceneBuilder::getRenderLayer(const nlohmann::json& data){

        return data.at("renderLayer").get<int>();
    }

    std::shared_ptr<Graphics::Texture> SceneBuilder::getTexture(const nlohmann::json& data){

        std::string spriteID = data.at("sprite").get<std::string>();

        return resourceManager.getTexture(spriteID);
    }

    std::shared_ptr<Graphics::Font> SceneBuilder::getFont(const nlohmann::json& data){

        std::string fontID = data.at("font").get<std::string>();

        return resourceManager.getFont(fontID);
    }

    Math::Vector2i SceneBuilder::getVector2i(const nlohmann::json& data, const std::string& key){

        int x = data.at(key)[0].get<int>();
        int y = data.at(key)[1].get<int>();

        return {x, y};

    }

    std::string SceneBuilder::getString(const nlohmann::json& data, const std::string& key){

        if(!data.contains(key)) throw std::runtime_error("SceneBuilder::getString: key not found: " + key);

        return data.at(key).get<std::string>();
    }

    void SceneBuilder::applyColorMask(const nlohmann::json& data, Attribute::Renderable& object){
        
        //Is not an array for background somehow
        if(!data.contains("colorMask") || !data.at("colorMask").is_array()) throw std::runtime_error("ColorMask not found for: an object");

        auto colors = data.at("colorMask");

        uint8_t red = colors[0];
        uint8_t green = colors[1];
        uint8_t blue = colors[2];
        uint8_t alpha = colors[3];

        Graphics::Color color{red, green, blue, alpha};

        object.setColor(color);
    }
/*
    void SceneBuilder::getDialogueController(const nlohmann::json& data, Components::DialogueBox& box){

        if(!data.contains("controller") || !data["controller"].is_object()) return;

        const auto& controllerData = data.at("controller");

        auto controller = std::make_shared<Moon::Core::DialogueController>(getString(controllerData, "id"));

        auto sequence = std::make_shared<Moon::Core::DialogueSequence>();
                
        size_t index = 0;//For the labels of jumpToDialogue

        for(const auto& line : controllerData.at("lines")){

            auto & currentLine = sequence->addLine(

                getString(line, "speaker"),
                getString(line, "text")
                );

                if(line.contains("label")){

                    const std::string label = getString(line, "label");

                    controller->registerLabel(label, index);

                }
                        
                if(line.contains("commands") && line["commands"].is_array()){

                    for(const auto& command : line.at("commands")){

                        if(!command.contains("action") || !command.contains("args") || !command.contains("target")) throw std::runtime_error("Moon::System::SceneBuilder:Invalid command format: " + command.dump(2));
                                
                        currentLine.addCommand(
                                    
                            getString(command, "action"),
                            command.at("args"),
                            getString(command, "target")
                        );

                    }
                }

                index ++;
            }

            controller->start(sequence);

            box.setController(controller);
        

    }*/
}