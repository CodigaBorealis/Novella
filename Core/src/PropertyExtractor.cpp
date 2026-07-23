#include "../Novella/Scene/Serialization/PropertyExtractor.hpp"
#include "../Novella/Scene/Parser/SceneDefinition.hpp"
#include "../Novella/Systems/Layout/Style.hpp"
#include <stdexcept>

namespace Novella::NScene::Serialization{

    SizeMode PropertyExtractor::getSizeMode(const std::string& value){

        if(value == "Fixed"){

            return SizeMode::Fixed;

        }else if(value  == "Percent"){

            return SizeMode::Percent;

        }else if(value  == "FitWidth"){

            return SizeMode::FitWidth;

        }else if(value  == "FitHeight"){

            return SizeMode::FitHeight;
        }

        throw std::runtime_error("Invalid value for property sizeMode '" + value +"'");
    }    

    Style PropertyExtractor::getStyle(const NScene::Parser::ObjectDefinition& object){

        Style layout{};

        auto* layoutNode = findChild(object, 4294967295);//The style type inside the parser

        if(!layoutNode) throw std::runtime_error("Missing layout block for '" + object.objectName + "'");
        
        if(auto* width = findProperty(*layoutNode, "width")){

            layout.width = width->value.as<double>();
        }

        if(auto* height = findProperty(*layoutNode, "height")){

            layout.height = height->value.as<double>();
        }

        if(auto* anchor = findProperty(*layoutNode, "anchor")){

            layout.anchor = getAnchor(anchor->value.as<std::string>());
        }

        if(auto* widthMode = findProperty(*layoutNode, "widthMode")){

            layout.widthMode = getSizeMode(widthMode->value.as<std::string>());
        }

        if(auto* heightMode = findProperty(*layoutNode, "heightMode")){

            layout.heightMode = getSizeMode(heightMode->value.as<std::string>());
        }

        if(auto* offset = findProperty(*layoutNode, "offset")){

            layout.offset = getVector<int>(*offset);
        }

        return layout;
    }

    const NScene::Parser::ObjectDefinition* PropertyExtractor::findChild(const NScene::Parser::ObjectDefinition& object, uint32_t type){

        for(const auto& child : object.children){

            if(child.objectType == type) return &child;
            
        }

        return nullptr;
    }  

    Anchor PropertyExtractor::getAnchor(const std::string& value){

        if(value == "TopLeft") return Anchor::TopLeft;

        if(value == "TopCenter") return Anchor::TopCenter;

        if(value == "TopRight") return Anchor::TopRight;

        if(value == "CenterLeft") return Anchor::CenterLeft;

        if(value == "Center") return Anchor::Center;

        if(value == "CenterRight") return Anchor::CenterRight;

        if(value == "BottomLeft") return Anchor::BottomLeft;

        if(value == "BottomCenter") return Anchor::BottomCenter;

        if(value == "BottomRight") return Anchor::BottomRight;

        throw std::runtime_error("Invalid anchor: " + value);
    }

    const NScene::Parser::Property* PropertyExtractor::findProperty(const NScene::Parser::ObjectDefinition& object, const std::string& name){

        for(const auto& property : object.properties){

            if(property.name == name) return &property;
        }

        return nullptr;
    }

    PropertyExtractor::CommonProps PropertyExtractor::extractCommon(const NScene::Parser::ObjectDefinition& definition){
        
        if(definition.objectName.empty()) throw std::runtime_error("Cannot build object without a valid name");

        return{definition.objectName, getStyle(definition), static_cast<int>(requireProperty<double>(definition, "renderLayer"))};

    }
}