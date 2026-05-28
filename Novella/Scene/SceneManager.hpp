#pragma once
#include "Scene.hpp"
#include <filesystem>
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <stdexcept>
#include <utility>

namespace Novella{

    namespace Rendering {
        
        class ResourceManager;

    }

    namespace Audio {
        
        class AudioSystem;

    }

    class SceneManager{

        public:

        SceneManager() = delete;

        SceneManager(Rendering::ResourceManager& resourceManager, Audio::AudioSystem& audio);
        
        void loadScene(std::unique_ptr<Scene> scene);

        Scene& getCurrentScene();
        Scene& createScene();

        template<typename T, typename ... Args>
        
        T& addObject(Args&&...args){

            if(!currentScene) throw std::runtime_error("SceneManager::addObject: No active scene");

            return currentScene->createObject<T>(std::forward<Args>(args)...);
        }

        void clear();

        private:

        std::unique_ptr<Scene> currentScene;
        Rendering::ResourceManager& resourceManager;
        Audio::AudioSystem& audioSystem;
    };

}