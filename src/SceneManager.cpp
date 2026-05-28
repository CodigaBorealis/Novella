#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/Audio/AudioSystem.hpp"
#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/Attribute/Object.hpp"
namespace Novella{

    SceneManager::SceneManager(Rendering::ResourceManager& resourceManager, Audio::AudioSystem& audio)
        :
        resourceManager(resourceManager),
        audioSystem(audio)
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

    void SceneManager::clear(){

        this->currentScene = nullptr;
    }
}
