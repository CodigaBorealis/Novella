#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/Audio/AudioSystem.hpp"
#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/IO/SceneLoader.hpp"
#include "../Novella/Attribute/Object.hpp"//clangd swears this file is unused, it IS used
#include "../Novella/Engine.hpp"
#include <memory>

namespace Novella{

    SceneManager::SceneManager(Resources::ResourceManager& resourceManager, Audio::AudioSystem& audio)
        :
        resourceManager(resourceManager),
        audioSystem(audio)
        {}

    void SceneManager::swapScene(std::unique_ptr<Scene> scene){

        currentScene = std::move(scene);

        if(currentScene->hasBgm()){

            audioSystem.play(currentScene->getBgm().value());
        }

    }

    Scene* SceneManager::getCurrentScene(){

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
        
        if(extension != ".nsc") throw std::runtime_error("Could not load the scene: expected a '.nsc' file got '" + extension + "'");

        sceneWatcher.setSceneFile(src);

        SceneLoader::Loader::load(engine, src);

    }
}
