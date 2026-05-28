#pragma once
#include <nlohmann/json_fwd.hpp>
#include <unordered_map>
#include <functional>
#include <memory>

namespace Novella::Attribute{

    class Object;

}

namespace Novella::Rendering{

    class ResourceManager;

}

namespace Novella{

    class ObjectFactory{

        using Creator = std::function<std::unique_ptr<Attribute::Object>(const nlohmann::json&, const Rendering::ResourceManager&)>;

        public:

        void registerType(const std::string& type, Creator creator);

        std::unique_ptr<Attribute::Object> create(const std::string& type, const nlohmann::json& data, const Rendering::ResourceManager& resourceManager);
        
        private:
        

        std::unordered_map<std::string, Creator> registry;
    };
}