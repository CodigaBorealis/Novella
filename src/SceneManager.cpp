#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/Scene/Serialization/SceneLoader.hpp"
#include "../Novella/Utils/FileSystem.hpp"
#include "../Novella/Project/EngineConfig.hpp"
#include "../Novella/Components/Traits/Object.hpp"//clangd swears this file is unused, it IS used
#include "../Novella/Scripting/Interpreter/RuntimeContext.hpp"
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
namespace Novella{

    SceneManager::SceneManager(ResourceManager& resourceManager, AudioSystem& audio)
        :
        resourceManager(resourceManager),
        audioSystem(audio)
        {}

    bool SceneManager::requestedSwap() const{

        return swapRequest != std::nullopt;
    }

    void SceneManager::registerScenes(const EngineConfig& config){

        for(const auto& pair : config.sceneData){

            sceneRegistry.emplace(pair.first,std::filesystem::path{pair.second});
            
        }

    }

    void SceneManager::requestSwap(const std::string& name){

        swapRequest = name;
    }

    void SceneManager::loadSceneFromName(NScript::Runtime::Context& context){

        if(swapRequest != std::nullopt){
        
            std::string name = swapRequest.value();

            auto it = sceneRegistry.find(name);

            if(it == sceneRegistry.end()) throw std::runtime_error("This scene is not registered on the project file: " + name);
            
            loadFile(context,  context.projectRoot / it->second);
        }
    }
        
    void SceneManager::loadFile(NScript::Runtime::Context& context, const std::filesystem::path& src){

        const std::string extension = src.extension().string();
        
        if(extension != ".nsc") throw std::runtime_error("Could not load the scene: expected a '.nsc' file got '" + extension + "'");

        if(!Utils::Filesystem::exists(src)) throw std::runtime_error("Could not load the scene: file not found '" + src.string() + "'");

        sceneWatcher.setSceneFile(src);

        NScene::Serialization::Loader::load(context, src);

        swapRequest = std::nullopt;
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
