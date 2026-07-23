#include "../Novella/Scene/Serialization/ComponentFactory.hpp"
#include "../Novella/Scene/Serialization/PropertyExtractor.hpp"
#include "../Novella/Scripting/Interpreter/RuntimeContext.hpp"
#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/Systems/Resources/ResourceManager.hpp"
#include "../Novella/Components/Components.hpp"
#include <stdexcept>
#include <string>
namespace Novella::NScene::Serialization{

    ComponentFactory::ComponentFactory(){

        registerDefaultComponents();
    }

    void ComponentFactory::registerType(uint32_t type, FactoryFunc creator){

        creators[type] = std::move(creator);
    }

    void ComponentFactory::build(uint32_t type, NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition& definition) const{

        auto it = creators.find(type);

        if(it == creators.end()) throw std::runtime_error("Unknown component type: " + std::to_string(type));

        it->second(context, definition);
    }

    void ComponentFactory::registerDefaultComponents(){

        registerType(UI::Sprite::getStaticTypeID(), [](NScript::Runtime::Context& context, const Parser::ObjectDefinition& definition){

            auto common = PropertyExtractor::extractCommon(definition);
            std::string texture = PropertyExtractor::requireProperty<std::string>(definition, "texture");

            context.scene->addObject<UI::Sprite>(

                common.name,
                context.resources->getTexture(texture),
                common.style,
                common.renderLayer
            );
        });

        registerType(UI::Label::getStaticTypeID(), [](NScript::Runtime::Context& context, const Parser::ObjectDefinition& definition){

            auto common = PropertyExtractor::extractCommon(definition);

            std::string font = PropertyExtractor::requireProperty<std::string>(definition, "font");
            std::string text = PropertyExtractor::requireProperty<std::string>(definition, "text");
            int size = static_cast<int>(PropertyExtractor::requireProperty<double>(definition, "size"));

            context.scene->addObject<UI::Label>(

                common.name,
                context.resources->getFont(font),
                text,
                size,
                common.style,
                common.renderLayer
            );
        });

        registerType(UI::Button::getStaticTypeID(), [](NScript::Runtime::Context& context, const Parser::ObjectDefinition& definition){
            
            auto handle = context.scene->addObject<UI::Button>(definition.objectName);

            auto* button = context.scene->getCurrentScene()->getObject<UI::Button>(handle);

            auto common = PropertyExtractor::extractCommon(definition);

            button->setStyle(common.style);
            button->setRenderLayer(common.renderLayer);

            if(auto texture = PropertyExtractor::optionalProperty<std::string>(definition, "texture")){

                button->setSprite(context.resources->getTexture(*texture), common.style, common.renderLayer);
            }

            auto font = PropertyExtractor::optionalProperty<std::string>(definition, "font");
            auto text = PropertyExtractor::optionalProperty<std::string>(definition, "text");
            auto fontSize = PropertyExtractor::optionalProperty<double>(definition, "fontSize");

            if(font && text && fontSize){

                button->setLabel(context.resources->getFont(*font), static_cast<int>(*fontSize), *text, common.style, common.renderLayer);
            }
        });
    }
}