#pragma once
#include "Scene.hpp"
#include "SceneWatcher.hpp"
#include <memory>
#include <stdexcept>
#include <utility>
#include "../Components/Traits/Object.hpp"

namespace Novella{
    
    class Engine;
        
    class ResourceManager;
        
    class AudioSystem;
    
    class SceneManager{

        public:

        SceneManager() = delete;

        SceneManager(ResourceManager& resourceManager, AudioSystem& audio);
        
        void swapScene(std::unique_ptr<Scene> scene);

        void loadSceneFromFile(Engine& engine, const std::filesystem::path& src);

        Scene* getCurrentScene();
        Scene& createScene();

        bool modifiedSceneFile();
        const std::filesystem::path currentSceneFile() const;

        void swapScene(Scene* scene);

        template<typename T, typename ... Args>
        
        T& addObject(Args&&...args){

            if(!currentScene) throw std::runtime_error("SceneManager::addObject: No active scene");

            return currentScene->createObject<T>(std::forward<Args>(args)...);
        }

        void clear();

        private:

        std::unique_ptr<Scene> currentScene = nullptr;
        SceneWatcher sceneWatcher;
        ResourceManager& resourceManager;
        AudioSystem& audioSystem;
    };

}