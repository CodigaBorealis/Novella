#include "../Novella/Scene/Serialization/ComponentBuilder.hpp"
#include "../Novella/Core/Engine.hpp"
#include "../Novella/Scene/Parser/SceneDefinition.hpp"
#include "../Novella/Systems/Layout/Style.hpp"
#include "../Novella/Components/UI/Button.hpp"
#include "../Novella/Components/UI/Label.hpp"
#include "../Novella/Components/UI/Sprite.hpp"
#include <stdexcept>

namespace Novella::NScene::Serialization{

    void ComponentBuilder::buildSprite(NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition& definition){

            if(definition.objectName.empty()) throw std::runtime_error("Can't create background object without a name");
            
            auto* tex = findProperty(definition, "texture");

            if(!tex) throw std::runtime_error("Missing texture property for '" + definition.objectName + "'");

            std::string texture = getString(*tex);

            Style style = getStyle(definition);

            auto* rlayer = findProperty(definition, "renderLayer");

            if(!rlayer) throw std::runtime_error("Missing renderLayer property for '" + definition.objectName + "'");

            int renderLayer = getInt(*rlayer);

            context.scene->addObject<UI::Sprite>(
                
                definition.objectName,
                context.resources->getTexture(texture),

                style,

                renderLayer
        );
    }


    void ComponentBuilder::buildButton(NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition& definition){

        if(definition.objectName.empty()) throw std::runtime_error("Can't create button object without a name");
            
        auto* tex = findProperty(definition, "texture");

        if(!tex) throw std::runtime_error("Missing texture property for '" + definition.objectName + "'");

        std::string texture = getString(*tex);

        Style constructedLayout = getStyle(definition);

        auto* rlayer = findProperty(definition, "renderLayer");

        if(!rlayer) throw std::runtime_error("Missing renderLayer property for '" + definition.objectName + "'");

        int renderLayer = getInt(*rlayer);

        context.scene->addObject<UI::Button>(

            definition.objectName,

            context.resources->getTexture(texture),

            constructedLayout,

            renderLayer

        );
    }


    void ComponentBuilder::buildLabel(NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition& definition){

      if(definition.objectName.empty()) throw std::runtime_error("Can't create background object without a name");
            
        auto* fnt = findProperty(definition, "font");

        if(!fnt) throw std::runtime_error("Missing font property for '" + definition.objectName + "'");

        auto* sz = findProperty(definition, "size");
        
        if(!sz) throw std::runtime_error("Missing size property for '" + definition.objectName + "'");

        int size = getInt(*sz);

        std::string font = getString(*fnt);

        auto* txt = findProperty(definition, "text");
        
        if(!txt) throw std::runtime_error("Missing text property for '" + definition.objectName + "'");
        
        std::string text = getString(*txt);
        
        Style constructedLayout = getStyle(definition);

        auto* rlayer = findProperty(definition, "renderLayer");

        if(!rlayer) throw std::runtime_error("Missing renderLayer property for '" + definition.objectName + "'");

        int renderLayer = getInt(*rlayer);

        context.scene->addObject<UI::Label>(

            definition.objectName,
            
            context.resources->getFont(font),
            
            size,
            
            text,
            constructedLayout,
            
            renderLayer

        );
    }

    SizeMode ComponentBuilder::getSizeMode(const NScene::Parser::Property& property){

        if(getString(property) == "Fixed"){

            return SizeMode::Fixed;

        }else if(getString(property)  == "Percent"){

            return SizeMode::Percent;

        }else if(getString(property)  == "FitWidth"){

            return SizeMode::FitWidth;

        }else if(getString(property)  == "FitHeight"){

            return SizeMode::FitHeight;
        }

        throw std::runtime_error("Invalid value for property sizeMode '" + property.value.as<std::string>() +"'");
    }    

    Style ComponentBuilder::getStyle(const NScene::Parser::ObjectDefinition& object){

        Style layout{};

        auto* layoutNode = findChild(object, 4294967295);//The style type inside the parser

        if(!layoutNode) throw std::runtime_error("Missing layout block for '" + object.objectName + "'");

        if(auto* width = findProperty(*layoutNode, "width")){

            layout.width = getInt(*width);
        }
        
        if(auto* height = findProperty(*layoutNode, "height")){

            layout.height = getInt(*height);
        }

        if(auto* anchor = findProperty(*layoutNode, "anchor")){

            layout.anchor = getAnchor(*anchor);
        }

        if(auto* widthMode = findProperty(*layoutNode, "widthMode")){

            layout.widthMode = getSizeMode(*widthMode);
        }

        if(auto* heightMode = findProperty(*layoutNode, "heightMode")){

            layout.heightMode = getSizeMode(*heightMode);
        }

        if(auto* offset = findProperty(*layoutNode, "offset")){

            layout.offset = getVector<int>(*offset);
        }

        return layout;
    }

    const NScene::Parser::ObjectDefinition* ComponentBuilder::findChild(const NScene::Parser::ObjectDefinition& object, uint32_t type){

        for(const auto& child : object.children){

            if(child.objectType == type) return &child;
            
        }

        return nullptr;
    }  

    Anchor ComponentBuilder::getAnchor(const NScene::Parser::Property& property){

        if(getString(property) == "TopLeft") return Anchor::TopLeft;

        if(getString(property) == "TopCenter") return Anchor::TopCenter;

        if(getString(property) == "TopRight") return Anchor::TopRight;

        if(getString(property) == "CenterLeft") return Anchor::CenterLeft;

        if(getString(property) == "Center") return Anchor::Center;

        if(getString(property) == "CenterRight") return Anchor::CenterRight;

        if(getString(property) == "BottomLeft") return Anchor::BottomLeft;

        if(getString(property) == "BottomCenter") return Anchor::BottomCenter;

        if(getString(property) == "BottomRight") return Anchor::BottomRight;

        throw std::runtime_error("Invalid anchor: " + property.name);
    }

    std::string ComponentBuilder::getString(const NScene::Parser::Property& property){

        if(!property.value.isString()) throw std::runtime_error("Invalid value for property' " + property.name + "' Expected a string");

        return property.value.as<std::string>();
    }

    int ComponentBuilder::getInt(const NScene::Parser::Property& property){

        if(!property.value.isNumber()) throw std::runtime_error("Expected int for property '" + property.name + "'");

        double rawValue = property.value.as<double>();

        if(std::trunc(rawValue) != rawValue) throw std::runtime_error("Expected int for property '" + property.name + "'");

        return static_cast<int>(rawValue);
    }

    const NScene::Parser::Property* ComponentBuilder::findProperty(const NScene::Parser::ObjectDefinition& object, const std::string& name){

        for(const auto& property : object.properties){

            if(property.name == name) return &property;
        }

        return nullptr;
    }
}