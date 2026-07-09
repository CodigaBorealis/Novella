#include "../Novella/Scripting/Interpreter/CoreInitializer.hpp"
#include "../Novella/Scripting/API/API.hpp"

namespace Novella::NScript::CoreInitializer{

    void registerWindow(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Window.";

        runtime.registerNativeFunction(prefix + "setTitle", Modules::Window::setTitle);

        runtime.registerNativeFunction(prefix + "setX", Modules::Window::setPositionX);
        runtime.registerNativeFunction(prefix + "setY", Modules::Window::setPositionY);
        runtime.registerNativeFunction(prefix + "setPosition", Modules::Window::setPosition);

        runtime.registerNativeFunction(prefix + "center", Modules::Window::center);
        runtime.registerNativeFunction(prefix + "close", Modules::Window::close);
        runtime.registerNativeFunction(prefix + "minimize", Modules::Window::minimize);
        runtime.registerNativeFunction(prefix + "maximize", Modules::Window::maximize);
        
        runtime.registerNativeFunction(prefix + "isFullScreen", Modules::Window::isFullScreen);
        runtime.registerNativeFunction(prefix + "isResizable", Modules::Window::isResizable);
        runtime.registerNativeFunction(prefix + "isFocused", Modules::Window::isFocused);

        runtime.registerNativeFunction(prefix + "setWidth", Modules::Window::setWidth);
        runtime.registerNativeFunction(prefix + "setHeight", Modules::Window::setHeight);
        runtime.registerNativeFunction(prefix + "setSize", Modules::Window::setSize);

        runtime.registerNativeFunction(prefix + "setIcon", Modules::Window::setIcon);
        
        runtime.registerNativeFunction(prefix + "width", Modules::Window::getWidth);
        runtime.registerNativeFunction(prefix + "height", Modules::Window::getHeight);
        runtime.registerNativeFunction(prefix + "x", Modules::Window::getPositionX);
        runtime.registerNativeFunction(prefix + "y", Modules::Window::getPositionY);
        runtime.registerNativeFunction(prefix + "title", Modules::Window::getTitle);
        
        
    }
    
    void registerRenderer(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Renderer.";
        runtime.registerNativeFunction(prefix + "setBackgroundColor", Modules::Renderer::setBackgroundColor);

    }

    void registerAudio(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Audio.";

        runtime.registerNativeFunction(prefix + "play", Modules::Audio::play);
        runtime.registerNativeFunction(prefix + "stop", Modules::Audio::stop);
        runtime.registerNativeFunction(prefix + "stopMusic", Modules::Audio::stopMusic);
        runtime.registerNativeFunction(prefix + "currentMusic", Modules::Audio::getCurrentMusic);

        runtime.registerNativeFunction(prefix + "setVolume", Modules::Audio::setVolume);
        runtime.registerNativeFunction(prefix + "setPan", Modules::Audio::setPan);
        runtime.registerNativeFunction(prefix + "setPitch", Modules::Audio::setPitch);

        runtime.registerNativeFunction(prefix + "masterVolume", Modules::Audio::getMasterVolume);
    }

    void registerScene(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Scene.";

        runtime.registerNativeFunction(prefix + "load", Modules::Scene::load);
        runtime.registerNativeFunction(prefix + "reload", Modules::Scene::reload);
        runtime.registerNativeFunction(prefix + "objectCount", Modules::Scene::objectCount);
    }

    void registerLogger(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Console.";

        runtime.registerNativeFunction(prefix + "print", Modules::Debug::print);
        runtime.registerNativeFunction(prefix + "clear", Modules::Debug::clear);
    }

    void registerMath(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Math.";

        runtime.registerNativeFunction(prefix + "clamp", Modules::Math::clamp);
        runtime.registerNativeFunction(prefix + "sqrt", Modules::Math::squareRoot);
        runtime.registerNativeFunction(prefix + "pow", Modules::Math::power);
        runtime.registerNativeFunction(prefix + "abs", Modules::Math::abs);
        runtime.registerNativeFunction(prefix + "min", Modules::Math::min);
        runtime.registerNativeFunction(prefix + "floor", Modules::Math::floor);
        runtime.registerNativeFunction(prefix + "ceil", Modules::Math::ceil);
        runtime.registerNativeFunction(prefix + "round", Modules::Math::round);
        runtime.registerNativeFunction(prefix + "sin", Modules::Math::sin);
        runtime.registerNativeFunction(prefix + "cos", Modules::Math::cos);
        runtime.registerNativeFunction(prefix + "tan", Modules::Math::tan);
        runtime.registerNativeFunction(prefix + "atan2", Modules::Math::atan2);
        runtime.registerNativeFunction(prefix + "degrees", Modules::Math::degToRad);
        runtime.registerNativeFunction(prefix + "radians", Modules::Math::radToDeg);
        runtime.registerNativeFunction(prefix + "lerp", Modules::Math::lerp);
        runtime.registerNativeFunction(prefix + "sign", Modules::Math::sign);
        runtime.registerNativeFunction(prefix + "pi", Modules::Math::pi);
        runtime.registerNativeFunction(prefix + "e", Modules::Math::e);
        runtime.registerNativeFunction(prefix + "phi", Modules::Math::phi);
        runtime.registerNativeFunction(prefix + "sqrt2", Modules::Math::sqrt2);
        runtime.registerNativeFunction(prefix + "sqrt3", Modules::Math::sqrt3);
        runtime.registerNativeFunction(prefix + "invPi", Modules::Math::invPi);
        runtime.registerNativeFunction(prefix + "invSqrtPi", Modules::Math::invSqrtPi);
        runtime.registerNativeFunction(prefix + "ln2", Modules::Math::ln2);
        runtime.registerNativeFunction(prefix + "ln10", Modules::Math::ln10);
        runtime.registerNativeFunction(prefix + "log2e", Modules::Math::log2e);
        runtime.registerNativeFunction(prefix + "log10e", Modules::Math::log10e);
        runtime.registerNativeFunction(prefix + "egamma", Modules::Math::egamma);


    }

    void registerString(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "String.";

        runtime.registerNativeFunction(prefix + "numberToString", Modules::String::numberToString);
        runtime.registerNativeFunction(prefix + "boolToString", Modules::String::boolToString);
        runtime.registerNativeFunction(prefix + "isBool", Modules::String::isBool);
        runtime.registerNativeFunction(prefix + "isNumber", Modules::String::isNumber);
        runtime.registerNativeFunction(prefix + "toBool", Modules::String::toBoolean);
        runtime.registerNativeFunction(prefix + "toNumber", Modules::String::toNumber);
        runtime.registerNativeFunction(prefix + "length", Modules::String::size);
        runtime.registerNativeFunction(prefix + "isEmpty", Modules::String::empty);
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

    void registerFilesystem(Runtime::RuntimeEnvironment &runtime){

        const std::string prefix = "FileSystem.";

        runtime.registerNativeFunction(prefix + "createFile", Modules::FileSystem::createFile);
        runtime.registerNativeFunction(prefix + "deleteFile", Modules::FileSystem::removeFile);
        runtime.registerNativeFunction(prefix + "createFolder", Modules::FileSystem::createFolder);
        runtime.registerNativeFunction(prefix + "removeFolder", Modules::FileSystem::removeFolder);
        runtime.registerNativeFunction(prefix + "move", Modules::FileSystem::moveFileToFolder);
    }

    void registerInput(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Input.";

        runtime.registerNativeFunction(prefix + "setCursor", Modules::Input::setCursorType);
        runtime.registerNativeFunction(prefix + "setCursorVisible", Modules::Input::setCursorVisible);
        runtime.registerNativeFunction(prefix + "lockCursor", Modules::Input::lockCursor);
        runtime.registerNativeFunction(prefix + "setCursorPosition", Modules::Input::setCursorPosition);
        runtime.registerNativeFunction(prefix + "moveCursor", Modules::Input::moveCursor);
        runtime.registerNativeFunction(prefix + "isKeyDown", Modules::Input::isKeyDown);
        runtime.registerNativeFunction(prefix + "isKeyPressed", Modules::Input::isKeyPressed);
        runtime.registerNativeFunction(prefix + "isKeyReleased", Modules::Input::isKeyReleased);
        runtime.registerNativeFunction(prefix + "isKeyUp", Modules::Input::isKeyUp);
        runtime.registerNativeFunction(prefix + "isMouseDown", Modules::Input::isMouseDown);
        runtime.registerNativeFunction(prefix + "isMousePressed", Modules::Input::isMousePressed);
        runtime.registerNativeFunction(prefix + "isMouseUp", Modules::Input::isMouseUp);
        runtime.registerNativeFunction(prefix + "isMouseReleased", Modules::Input::isMouseReleased);
        runtime.registerNativeFunction(prefix + "mouseX", Modules::Input::getMouseX);
        runtime.registerNativeFunction(prefix + "mouseY", Modules::Input::getMouseY);
        runtime.registerNativeFunction(prefix + "isMouseOver", Modules::Input::isMouseOver);
        runtime.registerNativeFunction(prefix + "isObjectClicked", Modules::Input::isObjectClicked);

    }

    void registerRandomModule(Runtime::RuntimeEnvironment &runtime){

        const std::string prefix = "Random.";

        runtime.registerNativeFunction(prefix + "int", Modules::Random::randomInt);
        runtime.registerNativeFunction(prefix + "float", Modules::Random::randomFloat);
        runtime.registerNativeFunction(prefix + "bool", Modules::Random::randomBool);
        runtime.registerNativeFunction(prefix + "string", Modules::Random::randomString);


    }
    
    void registerTransform(Runtime::RuntimeEnvironment& runtime){
        
        const std::string prefix = "Transform.";

        runtime.registerNativeFunction(prefix + "setRotation", Modules::Transform::setRotation);
        runtime.registerNativeFunction(prefix + "rotate", Modules::Transform::rotate);
        runtime.registerNativeFunction(prefix + "flipX", Modules::Transform::flipX);
        runtime.registerNativeFunction(prefix + "flipY", Modules::Transform::flipY);
        runtime.registerNativeFunction(prefix + "setX", Modules::Transform::setPositionX);
        runtime.registerNativeFunction(prefix + "setY", Modules::Transform::setPositionY);
        runtime.registerNativeFunction(prefix + "setPosition", Modules::Transform::setPosition);
        runtime.registerNativeFunction(prefix + "move", Modules::Transform::move);
        runtime.registerNativeFunction(prefix + "x", Modules::Transform::getX);
        runtime.registerNativeFunction(prefix + "y", Modules::Transform::getY);
        runtime.registerNativeFunction(prefix + "rotation", Modules::Transform::getRotation);

    }

    void registerSpriteModule(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Sprite.";
    
        runtime.registerNativeFunction(prefix + "setTexture", Modules::Sprite::setTexture);
        runtime.registerNativeFunction(prefix + "setColor", Modules::Sprite::setTint);  
    }


    void registerTextModule(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Label.";

        runtime.registerNativeFunction(prefix + "setText", Modules::Text::setText);
        runtime.registerNativeFunction(prefix + "text", Modules::Text::getText);
        runtime.registerNativeFunction(prefix + "setFont", Modules::Text::setFont);
        runtime.registerNativeFunction(prefix + "setSize", Modules::Text::setFontSize);
        runtime.registerNativeFunction(prefix + "setColor", Modules::Text::setFontColor);
        runtime.registerNativeFunction(prefix + "font", Modules::Text::getFont);
        runtime.registerNativeFunction(prefix + "size", Modules::Text::getFontSize);

    }

    
    void registerUIModule(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "UI.";

        runtime.registerNativeFunction(prefix + "createLabel", Modules::UI::createLabel);
        runtime.registerNativeFunction(prefix + "createButton", Modules::UI::createButton);
        runtime.registerNativeFunction(prefix + "createSprite", Modules::UI::createSprite);


    }

    void registerObjectModule(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Object.";

        runtime.registerNativeFunction(prefix + "get", Modules::Object::get);
        runtime.registerNativeFunction(prefix + "destroy", Modules::Object::destroy);
        runtime.registerNativeFunction(prefix + "exists", Modules::Object::exists);
        runtime.registerNativeFunction(prefix + "name", Modules::Object::getName);

    }

    void registerLayoutModule(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "Layout.";

        runtime.registerNativeFunction(prefix + "setWidth", Modules::Layout::setWidth);
        runtime.registerNativeFunction(prefix + "setHeight", Modules::Layout::setHeight);
        runtime.registerNativeFunction(prefix + "setSize", Modules::Layout::setSize);
        runtime.registerNativeFunction(prefix + "width", Modules::Layout::getWidth);
        runtime.registerNativeFunction(prefix + "height", Modules::Layout::getHeight);


    }

    #ifdef _WIN32
    void registerOS(Runtime::RuntimeEnvironment& runtime){
        
        const std::string prefix = "OS.";
        runtime.registerNativeFunction(prefix + "user", Modules::Win32::getUserEnv);
    }
    #endif

    #ifdef __linux__
    void registerOS(Runtime::RuntimeEnvironment& runtime){

        const std::string prefix = "OS.";

        runtime.registerNativeFunction(prefix + "user", Modules::Linux::getUserEnv);

    }
    
    #endif
}