#pragma once
#include "Scene.hpp"
#include "SceneWatcher.hpp"
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <stdexcept>
#include <utility>
#include "../Attribute/Object.hpp"

namespace Novella{
    
    class Engine;
    
    namespace Resources {
        
        class ResourceManager;

    }

    namespace Audio {
        
        class AudioSystem;

    }

    class SceneManager{

        public:

        SceneManager() = delete;

        SceneManager(Resources::ResourceManager& resourceManager, Audio::AudioSystem& audio);
        
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
        Resources::ResourceManager& resourceManager;
        Audio::AudioSystem& audioSystem;
    };

}