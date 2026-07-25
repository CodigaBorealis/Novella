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

        }else if(value == "FitContent"){

            return SizeMode::FitContent;
        }

        throw std::runtime_error("Invalid value for property sizeMode '" + value +"'");
    }    

    const NScene::Parser::ObjectDefinition* PropertyExtractor::findChild(const NScene::Parser::ObjectDefinition& object, const std::string& type){

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
        
        CommonProps common{};

        if(auto val = findProperty(definition, "anchor")){

            common.style.anchor = getAnchor(val->value.as<std::string>());
        }

        if(auto val = findProperty(definition, "widthMode")){

            common.style.widthMode = getSizeMode(val->value.as<std::string>());
        }

        if(auto val = findProperty(definition, "heightMode")){

            common.style.heightMode = getSizeMode(val->value.as<std::string>());
        }

        if(auto val = findProperty(definition, "width")){

            common.style.width = static_cast<int>(val->value.as<double>());
        }

        if(auto val = findProperty(definition, "height")){

            common.style.height = static_cast<int>(val->value.as<double>());
        }

        if(auto val = findProperty(definition, "offset")){

            common.style.offset = getVector<int>(*val);
        }

        if(auto val = findProperty(definition, "renderLayer")){

            common.renderLayer = static_cast<int>(val->value.as<double>());
        }

        return common;
    }
}