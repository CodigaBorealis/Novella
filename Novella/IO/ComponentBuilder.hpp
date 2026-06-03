#pragma once
#include <vector>
#include "../Math/Vector2x.hpp"
#include <stdexcept>
#include "../Syntax/Scene/SceneDefinition.hpp"

namespace Novella::Syntax::Scene {

    struct ObjectDefinition;
}

namespace Novella {

    class Scene;

    class Engine;

    struct Layout;

    enum class Anchor : int;

    enum class SizeMode : int;
};

namespace Novella::SceneLoader{

    template <typename T>
    concept FloatOrDouble =  std::is_same_v<T, float> || std::is_same_v<T, double>;

    class ComponentBuilder{

        public:
    
        static void buildBackground(Engine& engine, const Syntax::Scene::ObjectDefinition& definition);

        private:

        static int getInt(const Syntax::Scene::Property& property);

        static Layout getLayout(const Syntax::Scene::ObjectDefinition& object);

        static Anchor getAnchor(const Syntax::Scene::Property& anchorProperty);

        static const Syntax::Scene::Property* findProperty(const Syntax::Scene::ObjectDefinition& object, const std::string& name);

        static std::string getString(const Syntax::Scene::Property& property);

        static const Syntax::Scene::ObjectDefinition* findChild(const Syntax::Scene::ObjectDefinition& object, const std::string& name);

        template<FloatOrDouble T>
        
        static auto getNumber(const Syntax::Scene::Property& property){

            return static_cast<T>(property.value.numberValue);
        }
        
        template<typename T>

        static auto getVector(const Syntax::Scene::Property& property){

            const auto& values = property.value.arrayValues;

            if(values.size() != 2) throw std::runtime_error("'" + property.name +"' can't be converted to Vector2x: expected 2 values, got " +std::to_string(values.size()));

            if(values[0].type != Syntax::Scene::Value::Type::Number || values[1].type != Syntax::Scene::Value::Type::Number) throw std::runtime_error("'" + property.name + "' contains non-numeric values");

            return Math::Vector2x<T>{static_cast<T>(values[0].numberValue), static_cast<T>(values[1].numberValue)};
        }

        static SizeMode getSizeMode(const Syntax::Scene::Property& property);

    };

}