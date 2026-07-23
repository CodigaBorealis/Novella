#pragma once
#include "../../Core/Math/Vector2x.hpp"
#include <optional>
#include <stdexcept>
#include "../Parser/SceneDefinition.hpp"
#include "../../Systems/Layout/Style.hpp"

namespace Novella::NScene::Serialization{

    class PropertyExtractor{

        public:

        struct CommonProps{

            std::string name;
            Style style;
            int renderLayer;
        };

        static const NScene::Parser::Property* findProperty(const NScene::Parser::ObjectDefinition& object, const std::string& name);

        template<typename T>

        static auto getVector(const NScene::Parser::Property& property){

            const auto& values = property.value;

            if(!values.isArray()) throw std::runtime_error("'" + property.name + "' is not an array");

            if(values.size() != 2) throw std::runtime_error("'" + property.name +"' can't be converted to Vector2x: expected 2 values, got " +std::to_string(values.size()));

            if(!values.at(0).isNumber() || !values.at(1).isNumber()) throw std::runtime_error("'" + property.name + "' contains non-numeric values");

            return Vector2x<T>{static_cast<T>(values.at(0).as<double>()), static_cast<T>(values.at(1).as<double>())};
        }
//If you need an int require it as double and cast it, this breaks otherwise
        template<typename T>

        static T requireProperty(const NScene::Parser::ObjectDefinition& definition, const std::string& propertyName){

            auto* property = findProperty(definition, propertyName);

            return property->value.as<T>();
        }

        template<typename T>

        static std::optional<T> optionalProperty(const NScene::Parser::ObjectDefinition& definition, const std::string& propertyName){

            auto* prop = findProperty(definition, propertyName);

            if(!prop) return std::nullopt;

            return prop->value.as<T>();
        }

        static Anchor getAnchor(const std::string& value);

        static SizeMode getSizeMode(const std::string& value);

        static const NScene::Parser::ObjectDefinition* findChild(const NScene::Parser::ObjectDefinition& object, uint32_t typ);

        static Style getStyle(const NScene::Parser::ObjectDefinition& definition);

        static CommonProps extractCommon(const NScene::Parser::ObjectDefinition& definition);

    };

}