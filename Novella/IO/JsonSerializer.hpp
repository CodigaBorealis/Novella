#pragma once
#include "../Scene/Scene.hpp"
#include "../Scene/SceneBuilder.hpp"
#include "../Rendering/ResourceManager.hpp"
#include <filesystem>
#include <nlohmann/json.hpp>

namespace Novella::IO {

    class JsonSerializer{

        public:
        
        JsonSerializer(const Rendering::ResourceManager& manager);

        std::unique_ptr<Scene> deserializeScene(const nlohmann::json& data);
        nlohmann::json serializeScene(const Scene& scene);
        void saveScene(const std::string& name,const std::filesystem::path& location, const Scene& scene);
        nlohmann::json loadScene(const std::filesystem::path& file);
        
        private:

        SceneBuilder builder;

    };

}