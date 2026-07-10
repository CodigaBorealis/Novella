#pragma once
#include "Scene.hpp"
#include "SceneWatcher.hpp"
#include <memory>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>
#include "../Components/Traits/Object.hpp"
#include "../Project/EngineConfig.hpp"

namespace Novella::NScript::Runtime{

    struct Context;
}

namespace Novella{
    
    class Engine;
        
    class ResourceManager;
        
    class AudioSystem;
    
    class SceneManager{

        public:

        SceneManager() = delete;

        SceneManager(ResourceManager& resourceManager, AudioSystem& audio);

        bool requestedSwap() const;

        void requestSwap(const std::string& name);

        void registerScenes(const EngineConfig& config);

        void loadSceneFromName(NScript::Runtime::Context& context);

        void loadFile(NScript::Runtime::Context& context, const std::filesystem::path& src);

        const std::string& getSceneName(const std::filesystem::path& file) const;

        Scene* getCurrentScene();
        Scene& createScene();

        bool modifiedSceneFile();
        const std::filesystem::path currentSceneFile() const;

        template<typename T, typename ... Args>
        
        Handle addObject(const std::string& name, Args&&...args){

            if(!currentScene) throw std::runtime_error("SceneManager::addObject: No active scene");

            return currentScene->createObject<T>(name, std::forward<Args>(args)...);
        }

        void clear();

        private:

        std::unique_ptr<Scene> currentScene = nullptr;
        SceneWatcher sceneWatcher;
        ResourceManager& resourceManager;
        AudioSystem& audioSystem;

        std::optional<std::string> swapRequest;

        std::unordered_map<std::string, std::filesystem::path> sceneRegistry;
    };

}