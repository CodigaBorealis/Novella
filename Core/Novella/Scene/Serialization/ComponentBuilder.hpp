#pragma once
#include "../../Core/Math/Vector2x.hpp"
#include <stdexcept>
#include "../Parser/SceneDefinition.hpp"


namespace Novella{

    struct Style;

    enum class Anchor : int;

    enum class SizeMode : int;
}

namespace Novella {

    class Scene;

    class Engine;
};

namespace Novella::NScript::Runtime{

    struct Context;
}

namespace Novella::NScene::Serialization{

    class ComponentBuilder{

        public:
    
        static void buildSprite(NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition& definition);

        static void buildButton(NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition& definition);

        static void buildLabel(NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition& definition);

        private:

        static int getInt(const NScene::Parser::Property& property);

        static Style getStyle(const NScene::Parser::ObjectDefinition& object);

        static Anchor getAnchor(const NScene::Parser::Property& anchorProperty);

        static const NScene::Parser::Property* findProperty(const NScene::Parser::ObjectDefinition& object, const std::string& name);

        static std::string getString(const NScene::Parser::Property& property);

        static const NScene::Parser::ObjectDefinition* findChild(const NScene::Parser::ObjectDefinition& object, const uint32_t type);
        
        static double getNumber(const NScene::Parser::Property& property){

            if(!property.value.isNumber()) throw std::runtime_error("Property '" + property.name + "' is not a number");

            return std::get<double>(property.value.data);
        }
        
        template<typename T>

        static auto getVector(const NScene::Parser::Property& property){

            const auto& values = property.value;

            if(!values.isArray()) throw std::runtime_error("'" + property.name + "' is not an array");

            if(values.size() != 2) throw std::runtime_error("'" + property.name +"' can't be converted to Vector2x: expected 2 values, got " +std::to_string(values.size()));

            if(!values.at(0).isNumber() || !values.at(1).isNumber()) throw std::runtime_error("'" + property.name + "' contains non-numeric values");

            return Vector2x<T>{static_cast<T>(values.at(0).as<double>()), static_cast<T>(values.at(1).as<double>())};
        }

        static SizeMode getSizeMode(const NScene::Parser::Property& property);

    };

}