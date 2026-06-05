#include "../Novella/Engine.hpp"
#include "../Novella/Input/InputSystem.hpp"
#include <exception>
namespace Novella{

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps)
        :
        displayWindow(width, height , title, fps),
        sceneManager(resourceManager,audioSystem),
        windowRenderer(width, height),
        audioSystem(resourceManager)
            {}

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, WindowFlags flags)
        :
        displayWindow(width, height , title, fps, flags),
        sceneManager(resourceManager,audioSystem),
        windowRenderer(width, height),
        audioSystem(resourceManager)

            {}

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, const std::filesystem::path& icon)
        :
        displayWindow(width, height , title, fps, icon),
        sceneManager(resourceManager,audioSystem),
        windowRenderer(width, height),
        audioSystem(resourceManager)

            {}

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, const std::filesystem::path& icon, WindowFlags flags)
        :
        displayWindow(width, height , title, fps, icon, flags),
        sceneManager(resourceManager,audioSystem),
        windowRenderer(width, height),
        audioSystem(resourceManager)
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
                 
        }
    }

    Resources::ResourceManager& Engine::resources(){

        return this->resourceManager;
    }

    Rendering::Renderer& Engine::renderer(){

        return this->windowRenderer;
    }

    Audio::AudioSystem& Engine::audio(){

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

    Input::InteractionSystem& Engine::input(){

        return this->interactionSystem;
    }

    void Engine::computeLayout(Scene* currentScene){

        if(!currentScene) return;

        Math::Vector2i virtualResolution = {

                static_cast<int>(windowRenderer.virtualResolution().x),
                
                static_cast<int>(windowRenderer.virtualResolution().y)
            
        };

        layoutSystem.compute(*currentScene, virtualResolution);
        
    }
        void Engine::handleInput(Scene* currentScene){

            if(!currentScene) return;
            
            Math::Vector2f virtualMouse = windowRenderer.toVirtualCoordinates(Input::InputSystem::mousePosition());

            interactionSystem.handleKeyboardInput(*currentScene);

            interactionSystem.handleMouseInput(*currentScene, virtualMouse);

            CommandContext context{currentScene, &audioSystem, &windowRenderer, &displayWindow};

            interactionSystem.handleInteractions(context);
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
}