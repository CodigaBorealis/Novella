#include "../Novella/Scripting/Interpreter/CoreInitializer.hpp"
#include "../Novella/Scripting/API/API.hpp"

namespace Novella::NScript::CoreInitializer{

    void registerWindow(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Window.";

        runtime.registerNativeFunction(prefix + "setTitle", Modules::Window::setTitle);
        runtime.registerNativeFunction(prefix + "setPositionX", Modules::Window::setPositionX);
        runtime.registerNativeFunction(prefix + "setPositionY", Modules::Window::setPositionY);
        runtime.registerNativeFunction(prefix + "setWidth", Modules::Window::setWidth);
        runtime.registerNativeFunction(prefix + "setHeight", Modules::Window::setHeight);
        runtime.registerNativeFunction(prefix + "setIcon", Modules::Window::setIcon);
        runtime.registerNativeFunction(prefix + "getWidth", Modules::Window::getWidth);
        runtime.registerNativeFunction(prefix + "getHeight", Modules::Window::getWidth);
        runtime.registerNativeFunction(prefix + "getPositionX", Modules::Window::getPositionX);
        runtime.registerNativeFunction(prefix + "getPositionY", Modules::Window::getPositionX);
        runtime.registerNativeFunction(prefix + "getTitle", Modules::Window::getTitle);
        
    }
    
    void registerRenderer(Runtime::RuntimeEnvironment& runtime){

        
    }

    void registerAudio(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Audio.";

        runtime.registerNativeFunction(prefix + "play", Modules::Audio::play);
        runtime.registerNativeFunction(prefix + "stop", Modules::Audio::play);
        runtime.registerNativeFunction(prefix + "setVolume", Modules::Audio::volume);
    }

    void registerScene(Runtime::RuntimeEnvironment& runtime){

        
    }

    void registerLayout(Runtime::RuntimeEnvironment& runtime){

        
    }

    void registerInteraction(Runtime::RuntimeEnvironment& runtime){

        
    }

    void registerLogger(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Console.";

        runtime.registerNativeFunction(prefix + "print", Modules::Debug::print);
    }

}