#include "../Novella/Engine.hpp"

namespace Novella{

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps)
        :
        displayWindow(width, height , title, fps),
        sceneManager(resourceManager,audioSystem, serializer),
        serializer(resourceManager),
        windowRenderer(width, height)
        {}

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, WindowFlags flags)
        :
        displayWindow(width, height , title, fps, flags),
        sceneManager(resourceManager,audioSystem, serializer),
        serializer(resourceManager),
        windowRenderer(width, height)
        {}

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, const std::filesystem::path& icon)
        :
        displayWindow(width, height , title, fps, icon),
        sceneManager(resourceManager,audioSystem, serializer),
        serializer(resourceManager),
        windowRenderer(width, height)
        {}

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, const std::filesystem::path& icon, WindowFlags flags)
        :
        displayWindow(width, height , title, fps, icon, flags),
        sceneManager(resourceManager,audioSystem, serializer),
        serializer(resourceManager),
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

            layoutSystem.compute(currentScene, virtualResolution);
            
            windowRenderer.beginFrame();

            windowRenderer.drawScene(currentScene);

            windowRenderer.endFrame();

        }
    }

    Rendering::ResourceManager& Engine::resources(){

        return resourceManager;
    }

    Rendering::Renderer& Engine::renderer(){

        return windowRenderer;
    }

    Audio::AudioSystem& Engine::audio(){

        return audioSystem;
    }

    SceneManager& Engine::scene(){

        return sceneManager;
    }

    Window& Engine::window(){

        return displayWindow;
    }

    LayoutSystem& Engine::layout(){

        return layoutSystem;
    }
}