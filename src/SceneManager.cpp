#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/Audio/AudioSystem.hpp"
#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/IO/SceneLoader.hpp"
#include "../Novella/Attribute/Object.hpp"
#include "../Novella/Engine.hpp"
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

    Scene* SceneManager::getCurrentScene(){

        if(!currentScene) throw std::runtime_error("SceneManager::getCurrentScene: CurrentScene cannot be null");

        return currentScene.get();
    }
    
    Scene& SceneManager::createScene(){

        currentScene = std::make_unique<Scene>();

        return *currentScene;
    }

    void SceneManager::clear(){

        this->currentScene = nullptr;
    }

    bool SceneManager::modifiedSceneFile(){

        return sceneWatcher.hasFileChanged();
    }

    const std::filesystem::path SceneManager::currentSceneFile() const{

        return sceneWatcher.getSceneFile();
    }

    void SceneManager::loadSceneFromFile(Engine& engine,const std::filesystem::path& src){
        
        const std::string extension = src.extension().string();
        
        if(extension != ".nsc") throw std::runtime_error("Could not load the scene: expected a .nsc file got '" + extension + "'");

        sceneWatcher.setSceneFile(src);

        SceneLoader::Loader::load(engine, src);

    }

}
