#pragma once
#include <string>
#include <vector>

namespace Novella::Syntax::Scene{

    struct Value{

        enum class Type : unsigned int{

            String,
            Number,
            Boolean,
            Identifier,
            Array
        };

        Type type;
        std::string StringValue;
        double numberValue;
        bool boolValue;

        std::vector<Value> arrayValues;
    };

    struct Property{

        std::string name;
        Value value;
    };

    struct ObjectDefinition{

        std::string objectType;
        std::string objectName;
        std::vector<Property> properties;
        std::vector<ObjectDefinition> children;

    };
        
    struct ResourceDefinition{

        std::string type;
        std::string name;
        std::string path;
    };

    struct InputBindingDefinition{

        std::string targetName;
        std::string input;
        std::string commandAlias;
    };

    struct TransitionDefinition{

        std::string sceneName;
        std::string sceneFile;
    };

    struct SceneDefinition{

        std::string name;
        std::vector<ResourceDefinition> resources;
        std::vector<ObjectDefinition> objects;
        std::vector<InputBindingDefinition> inputs;
        std::vector<TransitionDefinition> transitions;

    };

}