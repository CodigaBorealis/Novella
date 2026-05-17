#pragma once
#include "../Rendering/ResourceManager.hpp"
#include "../Scene/Scene.hpp"
#include "../Math/Vector2x.hpp"
#include "ObjectFactory.hpp"
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include "../Components/Interactable.hpp"
#include "../Components/Clickable.hpp"
#include "../Components/DialogueBox.hpp"
#include "../Components/Renderable.hpp"
namespace Novella{

    class SceneBuilder{

        public:

        SceneBuilder() = delete;

        SceneBuilder(const Rendering::ResourceManager& resourceManager);

        std::unique_ptr<Scene> build(const nlohmann::json& data);

        //Avoids having to manually  cast back everything
        template<typename T>

        auto simpleBuilder(std::function<std::unique_ptr<T>(const nlohmann::json&, const Rendering::ResourceManager&)> function){

            return [function](const nlohmann::json& data, const Rendering::ResourceManager& resourceManager) -> std::unique_ptr<Attribute::Object>{

                return function(data, resourceManager);
            };
        }

        template<typename T, typename ConstructorFn, typename... PostFns>

        auto makeBuilder(ConstructorFn constructor, PostFns... postFns){

            return simpleBuilder<T>(
                [this, constructor, postFns...](const nlohmann::json& data, const Rendering::ResourceManager& resourceManager){

                    auto object = constructor(data, resourceManager);

                    (postFns(data, * object), ...);

                    return object;
                });
        }

        private:
        
        Math::Vector2i getVector2i(const nlohmann::json& array, const std::string& key);
        std::shared_ptr<Graphics::Texture> getTexture(const nlohmann::json& data);
        int getRenderLayer(const nlohmann::json& data);
        std::shared_ptr<Graphics::Font> getFont(const nlohmann::json& data);

        std::string getString(const nlohmann::json& data, const std::string& key);

        void getDialogueController(const nlohmann::json& data, Components::DialogueBox& box);

        void restoreMouseBinds(Attribute::Clickable& component, const nlohmann::json& data);
        void restoreKeybinds(Attribute::Interactable& component, const nlohmann::json& data);

        void applyColorMask(const nlohmann::json& data, Attribute::Renderable& object);

        const Rendering::ResourceManager& resourceManager;

        Scene& restoreBehaviour(Scene& scene, const nlohmann::json& data);

        void initFactory();
        ObjectFactory factory;
    };

}