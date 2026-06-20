#include "../Novella/IO/ComponentBuilder.hpp"
#include "../Novella/Engine.hpp"
#include "../Novella/Syntax/Scene/Parser.hpp"
#include "../Novella/Layout/Layout.hpp"
#include "../Novella/Layout/SizeMode.hpp"
#include "../Novella/Components/Button.hpp"
#include "../Novella/Components/Label.hpp"
#include "../Novella/Components/Sprite.hpp"
#include <stdexcept>

namespace Novella::SceneLoader{

    void ComponentBuilder::buildSprite(Engine& engine, const Syntax::Scene::ObjectDefinition& definition){

            if(definition.objectName.empty()) throw std::runtime_error("Can't create background object without an id");
            
            auto* tex = findProperty(definition, "texture");

            if(!tex) throw std::runtime_error("Missing texture property for '" + definition.objectName + "'");

            std::string texture = getString(*tex);

            Layout constructedLayout = getLayout(definition);

            auto* rlayer = findProperty(definition, "renderLayer");

            if(!rlayer) throw std::runtime_error("Missing renderLayer property for '" + definition.objectName + "'");

            int renderLayer = getInt(*rlayer);

            engine.scene().addObject<Components::Sprite>(

            engine.resources().getTexture(texture),

            constructedLayout,

            renderLayer

        );
        
    }

    void ComponentBuilder::buildButton(Engine &engine, const Syntax::Scene::ObjectDefinition &definition){
            
        if(definition.objectName.empty()) throw std::runtime_error("Can't create button object without an id");
            
        auto* tex = findProperty(definition, "texture");

        if(!tex) throw std::runtime_error("Missing texture property for '" + definition.objectName + "'");

        std::string texture = getString(*tex);

        Layout constructedLayout = getLayout(definition);

        auto* rlayer = findProperty(definition, "renderLayer");

        if(!rlayer) throw std::runtime_error("Missing renderLayer property for '" + definition.objectName + "'");

        int renderLayer = getInt(*rlayer);

        engine.scene().addObject<Components::Button>(

            engine.resources().getTexture(texture),

            constructedLayout,

            renderLayer

        );
    }

    void ComponentBuilder::buildLabel(Engine &engine, const Syntax::Scene::ObjectDefinition &definition){
        
        if(definition.objectName.empty()) throw std::runtime_error("Can't create background object without an id");
            
        auto* fnt = findProperty(definition, "font");

        if(!fnt) throw std::runtime_error("Missing font property for '" + definition.objectName + "'");

        auto* sz = findProperty(definition, "size");
        
        if(!sz) throw std::runtime_error("Missing size property for '" + definition.objectName + "'");

        int size = getInt(*sz);

        std::string font = getString(*fnt);

        auto* txt = findProperty(definition, "text");
        
        if(!txt) throw std::runtime_error("Missing text property for '" + definition.objectName + "'");
        
        std::string text = getString(*txt);
        
        Layout constructedLayout = getLayout(definition);

        auto* rlayer = findProperty(definition, "renderLayer");

        if(!rlayer) throw std::runtime_error("Missing renderLayer property for '" + definition.objectName + "'");

        int renderLayer = getInt(*rlayer);

        engine.scene().addObject<Components::Label>(

            engine.resources().getFont(font),
            
            size,
            
            text,
            constructedLayout,
            
            renderLayer

        );
    }
    SizeMode ComponentBuilder::getSizeMode(const Syntax::Scene::Property& property){

        if(property.value.StringValue == "Fixed"){

            return SizeMode::Fixed;

        }else if(property.value.StringValue == "Percent"){

            return SizeMode::Percent;

        }else if(property.value.StringValue == "FitWidth"){

            return SizeMode::FitWidth;

        }else if(property.value.StringValue == "FitHeight"){

            return SizeMode::FitHeight;
        }

        throw std::runtime_error("Invalid value for property sizeMode '" + property.value.StringValue +"'");
    }    

    Layout ComponentBuilder::getLayout(const Syntax::Scene::ObjectDefinition& object){

        Layout layout{};

        auto* layoutNode = findChild(object, "layout");

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

    const Syntax::Scene::ObjectDefinition* ComponentBuilder::findChild(const Syntax::Scene::ObjectDefinition& object, const std::string& type){

        for(const auto& child : object.children){

            if(child.objectType == type) return &child;
            
        }

        return nullptr;
    }  

    Anchor ComponentBuilder::getAnchor(const Syntax::Scene::Property& property){

        if(property.value.StringValue == "TopLeft") return Anchor::TopLeft;

        if(property.value.StringValue == "TopCenter") return Anchor::TopCenter;

        if(property.value.StringValue == "TopRight") return Anchor::TopRight;

        if(property.value.StringValue == "CenterLeft") return Anchor::CenterLeft;

        if(property.value.StringValue == "Center") return Anchor::Center;

        if(property.value.StringValue == "CenterRight") return Anchor::CenterRight;

        if(property.value.StringValue == "BottomLeft") return Anchor::BottomLeft;

        if(property.value.StringValue == "BottomCenter") return Anchor::BottomCenter;

        if(property.value.StringValue == "BottomRight") return Anchor::BottomRight;

        throw std::runtime_error("Invalid value for property anchor '" + property.value.StringValue +"'");
    }

    std::string ComponentBuilder::getString(const Syntax::Scene::Property& string){

        return string.value.StringValue;
    }

    int ComponentBuilder::getInt(const Syntax::Scene::Property& property){

        if(std::trunc(property.value.numberValue) != property.value.numberValue) throw std::runtime_error("Expected int for property '" + property.name + "'");

        return  property.value.numberValue;
    }

    const Syntax::Scene::Property* ComponentBuilder::findProperty(const Syntax::Scene::ObjectDefinition& object, const std::string& name){

        for(const auto& property : object.properties){

            if(property.name == name) return &property;
        }

        return nullptr;
    }
}