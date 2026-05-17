#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/Audio/AudioSystem.hpp"
#include "../Novella/IO/JsonSerializer.hpp"
namespace Novella{

    SceneManager::SceneManager(Rendering::ResourceManager& resourceManager, Audio::AudioSystem& audio, IO::JsonSerializer& serializer)
        :
        resourceManager(resourceManager),
        audioSystem(audio),
        serializer(serializer)
        {}

    void SceneManager::loadScene(std::unique_ptr<Scene> scene){

        currentScene = std::move(scene);

        if(currentScene->hasBgm()){

            audioSystem.play(currentScene->getBgm().value());
        }

    }

    Scene& SceneManager::getCurrentScene(){

        if(!currentScene) throw std::runtime_error("SceneManager::getCurrentScene: CurrentScene cannot be null");

        return *currentScene;
    }
    
    Scene& SceneManager::createScene(){

        currentScene = std::make_unique<Scene>();

        return *currentScene;
    }

    void SceneManager::saveCurrentScene(const std::filesystem::path& location, const std::string& name){

        if(!currentScene) return;

        serializer.saveScene(name, location, *currentScene);
    }

    void SceneManager::saveScene(const std::string& name,const std::filesystem::path& location, const Scene& scene){

        serializer.saveScene(name, location, scene);
    }

    void SceneManager::clear(){

        this->currentScene = nullptr;
    }
}
