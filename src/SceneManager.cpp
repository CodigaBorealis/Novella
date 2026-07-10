#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/Scene/Serialization/SceneLoader.hpp"
#include "../Novella/Utils/FileSystem.hpp"
#include "../Novella/Project/EngineConfig.hpp"
#include "../Novella/Components/Traits/Object.hpp"//clangd swears this file is unused, it IS used
#include "../Novella/Scripting/Interpreter/RuntimeContext.hpp"
#include <memory>
#include <stdexcept>
namespace Novella{

    SceneManager::SceneManager(ResourceManager& resourceManager, AudioSystem& audio)
        :
        resourceManager(resourceManager),
        audioSystem(audio)
        {}

    void SceneManager::registerScenes(const EngineConfig& config){

        for(const auto& pair : config.sceneData){

            sceneRegistry.emplace(pair.first,std::filesystem::path{pair.second});
            
        }

    }

    void SceneManager::loadSceneFromName(NScript::Runtime::Context& context, const std::string& name){

        auto it = sceneRegistry.find(name);

        if(it == sceneRegistry.end()) throw std::runtime_error("This scene is not registered on the project file: " + name);

        loadSceneFromFile(context,  context.projectRoot / it->second);
    }
        
    void SceneManager::loadSceneFromFile(NScript::Runtime::Context& context, const std::filesystem::path& src){

        const std::string extension = src.extension().string();
        
        if(extension != ".nsc") throw std::runtime_error("Could not load the scene: expected a '.nsc' file got '" + extension + "'");

        if(!Utils::Filesystem::exists(src)) throw std::runtime_error("Could not load the scene: file not found '" + src.string() + "'");

        sceneWatcher.setSceneFile(src);

        NScene::Serialization::Loader::load(context, src);
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
}
