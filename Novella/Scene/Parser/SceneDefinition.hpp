#pragma once
#include <cstddef>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>
#include <cstdint>

namespace Novella::NScene::Parser{

    struct Value;

    using ValueData = std::variant<bool, double, std::string, std::vector<Value>>;

    struct Value{

        ValueData data;

        bool isIdentifier = false;

        bool isBool() const{return std::holds_alternative<bool>(data);}
        bool isNumber() const{return std::holds_alternative<double>(data);}
        bool isString() const{return std::holds_alternative<std::string>(data);}
        bool isArray() const{return std::holds_alternative<std::vector<Value>>(data);}
//This is kind of shit but its only used in two files so its fine

        template<typename T>

        const T& as() const{

            return std::get<T>(data);
        }

        template<typename T>

        T& as(){

            return std::get<T>(data);
        }

        size_t size() const{

            if(isArray()) return std::get<std::vector<Value>>(data).size();

            throw std::runtime_error("data is not an array");
        }

        Value& at(size_t index){

            if(isArray()) return std::get<std::vector<Value>>(data).at(index);

            throw std::runtime_error("data is not an array");
        }

        const Value& at(size_t index) const{

            if(isArray()) return std::get<std::vector<Value>>(data).at(index);

            throw std::runtime_error("data is not an array");
        }
    };

    struct Property{

        std::string name;
        Value value;
    };

    struct ObjectDefinition{

        uint32_t objectType;
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