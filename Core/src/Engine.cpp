#include "../Novella/Core/Engine.hpp"
#include <exception>
#include <memory>
#include <stdexcept>
#include "../Novella/Project/Project.hpp"
#include "../Novella/Utils/FileSystem.hpp"
namespace Novella{

    std::unique_ptr<Engine> Engine::singleInstance = nullptr;

    Engine& Engine::create(const std::filesystem::path& configFile){

        if(singleInstance) throw std::runtime_error("Can't create more than one instance of the engine");
        
        auto configPath = Utils::Filesystem::findProjectFile(configFile);

        EngineConfig config = Project::load(configPath);

        singleInstance = std::unique_ptr<Engine>(new Engine(config, configPath.parent_path()));

        return *singleInstance;
    }

    Engine::Engine(const EngineConfig& config, const std::filesystem::path& projectRoot)
        :
        root(projectRoot),
        displayWindow(config.width, config.height , config.title, config.targetFPS, root / config.icon, config.flags),
        sceneManager(resourceManager,audioSystem),
        windowRenderer(config.width, config.height),
        audioSystem(resourceManager){

                interpreter.initialize(*this);
                sceneManager.registerScenes(config);
            }

    const std::filesystem::path& Engine::projectRoot() const{

        return root;
    }

    void Engine::run(){
        
        while(displayWindow.isOpen()){
                        
            if(sceneManager.requestedSwap()) sceneManager.loadSceneFromName(interpreter.runtimeContext());

            if(sceneManager.modifiedSceneFile()){

            try{

                sceneManager.loadFile(interpreter.runtimeContext(), sceneManager.currentSceneFile());

                lastError.clear();

            }catch(const std::exception& e){

                lastError = e.what();
            }

            }

            if(displayWindow.isResized()){

                windowRenderer.resize(displayWindow.getSize());

            }

            handleAudio(sceneManager.getCurrentScene());
            computeLayout(sceneManager.getCurrentScene());
            handleRendering(sceneManager.getCurrentScene());     
            handleScripting(sceneManager.getCurrentScene());    
                 
        }
    }

    ResourceManager& Engine::resources(){

        return this->resourceManager;
    }

    Renderer& Engine::renderer(){

        return this->windowRenderer;
    }

    AudioSystem& Engine::audio(){

        return this->audioSystem;
    }

    SceneManager& Engine::scene(){

        return this->sceneManager;
    }

    Window& Engine::window(){

        return this->displayWindow;
    }

    LayoutSystem& Engine::layout(){

        return this->layoutSystem;
    }

    NScript::Runtime::Interpreter& Engine::script(){

        return this->interpreter;
    }

    void Engine::computeLayout(Scene* currentScene){

        if(!currentScene) return;

        Vector2i virtualResolution = {

                static_cast<int>(windowRenderer.virtualResolution().x),
                
                static_cast<int>(windowRenderer.virtualResolution().y)
            
        };

        layoutSystem.compute(*currentScene, virtualResolution);
        
    }
        void Engine::handleRendering(Scene* currentScene){

            windowRenderer.beginFrame();

            if(currentScene){

                windowRenderer.drawScene(*currentScene);

            }

            if(!lastError.empty()){

                windowRenderer.drawErrorMessage(lastError);
            }

            windowRenderer.endFrame();
        }

    void Engine::loadScene(const std::string& name){

        sceneManager.requestSwap(name);
    }

    void Engine::handleAudio(Scene* scene){

        if(!scene) return;

        audioSystem.update();
    }

    void Engine::handleScripting(Scene* scene){

        if(!scene) return;

        interpreter.run();
    }   

    Logger& Engine::logger(){

        return lg;
    }
}