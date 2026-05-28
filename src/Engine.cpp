#include "../Novella/Engine.hpp"
#include "../Novella/Input/InputSystem.hpp"

namespace Novella{

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps)
        :
        displayWindow(width, height , title, fps),
        sceneManager(resourceManager,audioSystem),
        windowRenderer(width, height)
            {}

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, WindowFlags flags)
        :
        displayWindow(width, height , title, fps, flags),
        sceneManager(resourceManager,audioSystem),
        windowRenderer(width, height)
            {}

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, const std::filesystem::path& icon)
        :
        displayWindow(width, height , title, fps, icon),
        sceneManager(resourceManager,audioSystem),
        windowRenderer(width, height)
            {}

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, const std::filesystem::path& icon, WindowFlags flags)
        :
        displayWindow(width, height , title, fps, icon, flags),
        sceneManager(resourceManager,audioSystem),
        windowRenderer(width, height)
            {}

    void Engine::run(){
        
        while(displayWindow.isOpen()){

            auto& currentScene = sceneManager.getCurrentScene();

            audioSystem.update();

            if(displayWindow.isResized()){

                windowRenderer.resize(displayWindow.getSize());

            }
            
            Math::Vector2i virtualResolution = {

                static_cast<int>(windowRenderer.virtualResolution().x),
                
                static_cast<int>(windowRenderer.virtualResolution().y)
            
            };

            Math::Vector2f virtualMouse = windowRenderer.toVirtualCoordinates(Input::InputSystem::mousePosition());

            layoutSystem.compute(currentScene, virtualResolution);

            interactionSystem.handleKeyboardInput(currentScene);

            interactionSystem.handleMouseInput(currentScene, virtualMouse);

            windowRenderer.beginFrame();

            windowRenderer.drawScene(currentScene);

            windowRenderer.endFrame();

        }
    }

    Rendering::ResourceManager& Engine::resources(){

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

}