#pragma once
#include "Scene.hpp"
#include "SceneWatcher.hpp"
#include <memory>
#include <stdexcept>
#include <utility>
#include "../Components/Traits/Object.hpp"

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
        
        void loadSceneFromName(const std::string& name);

        void loadSceneFromFile(NScript::Runtime::Context& context, const std::filesystem::path& src);
        void loadSceneFromFile(Engine& engine, const std::filesystem::path& src);

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
    };

}