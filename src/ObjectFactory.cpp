#include "../Novella/Scene/ObjectFactory.hpp"
#include "../Novella/Attribute/Object.hpp"
#include <stdexcept>

namespace Novella{
    
    void ObjectFactory::registerType(const std::string& type, Creator creator){

        registry[type] = creator;
    }

    std::unique_ptr<Attribute::Object> ObjectFactory::create(const std::string& type, const nlohmann::json& data, const Rendering::ResourceManager& resourceManager){

        auto it = registry.find(type);

        if(it == registry.end()) throw std::runtime_error("ObjectFactory::create: Unkown type" + type);

        return it->second(data, resourceManager);
    }


}