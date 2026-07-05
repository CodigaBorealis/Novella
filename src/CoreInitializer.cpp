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
        runtime.registerNativeFunction(prefix + "getHeight", Modules::Window::getHeight);
        runtime.registerNativeFunction(prefix + "getPositionX", Modules::Window::getPositionX);
        runtime.registerNativeFunction(prefix + "getPositionY", Modules::Window::getPositionY);
        runtime.registerNativeFunction(prefix + "getTitle", Modules::Window::getTitle);
        
    }
    
    void registerRenderer(Runtime::RuntimeEnvironment& runtime){

        
    }

    void registerAudio(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Audio.";

        runtime.registerNativeFunction(prefix + "play", Modules::Audio::play);
        runtime.registerNativeFunction(prefix + "stop", Modules::Audio::stop);
        runtime.registerNativeFunction(prefix + "stopMusic", Modules::Audio::stopMusic);
        runtime.registerNativeFunction(prefix + "getCurrentMusic", Modules::Audio::getCurrentMusic);
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

    void registerMath(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Math.";

        runtime.registerNativeFunction(prefix + "randomRange", Modules::Math::randomRange);
        runtime.registerNativeFunction(prefix + "clamp", Modules::Math::clamp);
        runtime.registerNativeFunction(prefix + "squareRoot", Modules::Math::squareRoot);
        runtime.registerNativeFunction(prefix + "power", Modules::Math::power);
    }

    void registerString(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "String.";

        runtime.registerNativeFunction(prefix + "numberToString", Modules::String::numberToString);
        runtime.registerNativeFunction(prefix + "boolToString", Modules::String::boolToString);
        runtime.registerNativeFunction(prefix + "isBool", Modules::String::isBool);
        runtime.registerNativeFunction(prefix + "isNumber", Modules::String::isNumber);
        runtime.registerNativeFunction(prefix + "toBool", Modules::String::toBoolean);
        runtime.registerNativeFunction(prefix + "toNumber", Modules::String::toNumber);
        runtime.registerNativeFunction(prefix + "size", Modules::String::size);
        runtime.registerNativeFunction(prefix + "empty", Modules::String::empty);
        runtime.registerNativeFunction(prefix + "toUpper", Modules::String::toUpper);
        runtime.registerNativeFunction(prefix + "toLower", Modules::String::toLower);
        runtime.registerNativeFunction(prefix + "capitalize", Modules::String::capitalize);
        runtime.registerNativeFunction(prefix + "contains", Modules::String::contains);
        runtime.registerNativeFunction(prefix + "startsWith", Modules::String::startsWith);
        runtime.registerNativeFunction(prefix + "endsWith", Modules::String::endsWith);
        runtime.registerNativeFunction(prefix + "indexOf", Modules::String::indexOf);
        runtime.registerNativeFunction(prefix + "lastIndexOf", Modules::String::lastIndexOf);
        runtime.registerNativeFunction(prefix + "remove", Modules::String::remove);
        runtime.registerNativeFunction(prefix + "replace", Modules::String::replace);
        runtime.registerNativeFunction(prefix + "replaceFirst", Modules::String::replaceFirst);
        runtime.registerNativeFunction(prefix + "replaceLast", Modules::String::replaceLast);
        runtime.registerNativeFunction(prefix + "trim", Modules::String::trim);
        runtime.registerNativeFunction(prefix + "trimLeft", Modules::String::trimLeft);
        runtime.registerNativeFunction(prefix + "trimRight", Modules::String::trimRight);
        runtime.registerNativeFunction(prefix + "substringFrom", Modules::String::substringFrom);
        runtime.registerNativeFunction(prefix + "charAt", Modules::String::charAt);
        runtime.registerNativeFunction(prefix + "equalsIgnoreCase", Modules::String::equalsIgnoreCase);
        runtime.registerNativeFunction(prefix + "reverse", Modules::String::reverse);
    }

}