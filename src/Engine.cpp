#include "../Novella/Core/Engine.hpp"
#include "../Novella/Systems/Input/InteractionSystem.hpp"
#include "../Novella/Systems/Input/InputSystem.hpp"
#include <exception>

namespace Novella{
//Later
    Engine::Engine()
        :
        displayWindow(1280, 720, "Novella Engine", 60),
        sceneManager(resourceManager, audioSystem),
        windowRenderer(1280, 720),
        audioSystem(resourceManager)
        //interpreter(runtime)
        //interactionSystem(interpreter)
        {}
        
    Engine::Engine(const EngineConfig& config)
        :
        displayWindow(config.width, config.height , config.title, config.targetFPS),
        sceneManager(resourceManager,audioSystem),
        windowRenderer(config.width, config.height),
        audioSystem(resourceManager)
        //interpreter(RuntimeEnvironment &runtime)
        //interactionSystem(interpreter)
            {}

    void Engine::run(){
        
        while(displayWindow.isOpen()){
                        
            if(sceneManager.modifiedSceneFile()){

            try{

                sceneManager.loadSceneFromFile(*this, sceneManager.currentSceneFile());

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
            handleInput(sceneManager.getCurrentScene());
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
/*
    InteractionSystem& Engine::input(){

        //return this->interactionSystem;
    }

    NScript::Runtime::Interpreter& Engine::script(){

        //return this->interpreter;
    }
*/
    void Engine::computeLayout(Scene* currentScene){

        if(!currentScene) return;

        Vector2i virtualResolution = {

                static_cast<int>(windowRenderer.virtualResolution().x),
                
                static_cast<int>(windowRenderer.virtualResolution().y)
            
        };

        layoutSystem.compute(*currentScene, virtualResolution);
        
    }
        void Engine::handleInput(Scene* currentScene){

            if(!currentScene) return;
            
            Vector2f virtualMouse = windowRenderer.toVirtualCoordinates(InputSystem::mousePosition());

            //interactionSystem.handleKeyboardInput(*currentScene);

            //interactionSystem.handleMouseInput(*currentScene, virtualMouse);

            //interactionSystem.handleInteractions();
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

    void Engine::loadSceneFromFile(const std::filesystem::path& src){
        
        sceneManager.loadSceneFromFile(*this, src);
        
    }

    void Engine::handleAudio(Scene* scene){

        if(!scene) return;

        audioSystem.update();
    }

    void Engine::handleScripting(Scene* scene){

        if(!scene) return;

    }

    Logger& Engine::logger(){

        return lg;
    }
}