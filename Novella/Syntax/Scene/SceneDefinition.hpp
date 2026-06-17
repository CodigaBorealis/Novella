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

    struct ScriptDefinition{

        std::string name;
        std::string path;
    };

    struct SceneDefinition{

        std::vector<Property> windowProperties;
        std::vector<ResourceDefinition> resources;
        std::vector<ObjectDefinition> objects;
        std::vector<ScriptDefinition> scripts;
    };

}