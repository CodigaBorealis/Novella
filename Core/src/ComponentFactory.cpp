#include "../Novella/Scene/Serialization/ComponentFactory.hpp"
#include "../Novella/Scene/Serialization/PropertyExtractor.hpp"
#include "../Novella/Scripting/Interpreter/RuntimeContext.hpp"
#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/Systems/Resources/ResourceManager.hpp"
#include "../Novella/Components/Components.hpp"
#include <memory>
#include <string>
namespace Novella::NScene::Serialization{

    ComponentFactory::ComponentFactory(){

        registerDefaultComponents();
    }

    void ComponentFactory::registerType(const std::string& type, FactoryFunc creator){

        creators[type] = std::move(creator);
    }

    std::unique_ptr<Traits::Object> ComponentFactory::build(NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition& definition) const{

        std::unique_ptr<Traits::Object> object;

        auto it = creators.find(definition.objectType);

        if(it != creators.end()){
            
            object = it->second(context, definition);

        }else{

            object = std::make_unique<Generic::UserWidget>();

        }

        if(auto* composite = dynamic_cast<Traits::Composite*>(object.get())){

            for(const auto& child : definition.children){

                auto childObject = build(context, child);

                composite->addChild(child.objectName, std::move(childObject));
            }
        }

        return object;
    }

    void ComponentFactory::registerDefaultComponents(){

        registerType("Sprite", [](NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition& definition){

            auto common = PropertyExtractor::extractCommon(definition);
            std::string texture = PropertyExtractor::requireProperty<std::string>(definition, "texture");
            
            return std::make_unique<UI::Sprite>(

                context.resources->getTexture(texture),
                 common.style,
                  common.renderLayer);
        });

        registerType("Label", [](NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition& definition){

            auto common = PropertyExtractor::extractCommon(definition);

            std::string font = PropertyExtractor::requireProperty<std::string>(definition, "font");
            std::string text = PropertyExtractor::requireProperty<std::string>(definition, "text");
            int size = static_cast<int>(PropertyExtractor::requireProperty<double>(definition, "size"));

            
            return std::make_unique<UI::Label>(
    
                context.resources->getFont(font),
                text,
                size,
                common.style,
                common.renderLayer);
        });

           registerType("Button", [](NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition& definition){
            
            auto common = PropertyExtractor::extractCommon(definition);

            auto button = std::make_unique<UI::Button>();

            button->setStyle(common.style);
            button->setRenderLayer(common.renderLayer);

            return button;
        });     

        registerType("DialogueBox", [](NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition& definition){
            
            auto common = PropertyExtractor::extractCommon(definition);

            auto box = std::make_unique<UI::DialogueBox>();

            box->setStyle(common.style);
            box->setRenderLayer(common.renderLayer);

            return box;
        });   
    }

    std::unique_ptr<Traits::Object> ComponentFactory::create(NScript::Runtime::Context& context, const Parser::ObjectDefinition& definition){

        auto object = build(context, definition);

        if(auto* validatable = dynamic_cast<Traits::Validatable*>(object.get())){

            validatable->validate();
        }

        return object;
    }
}