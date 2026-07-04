#include "../Novella/Scripting/API/WindowModule.hpp"
#include "../Novella/Windowing/Window.hpp"
#include <filesystem>
#include "../Novella/Scripting/Interpreter/RuntimeEnvironment.hpp"

namespace Novella::NScript::Modules::Window{

    void setTitle(Runtime::Context& context, const std::string& title){

        context.window->setTitle(title);
    }

    void setPosition(Runtime::Context& context, const Vector2i& position){

        context.window->setPosition(position);
    }

    void move(Runtime::Context& context, const Vector2i& delta){
    
        Vector2i position = context.window->getPosition();

        position.x += delta.x;
        position.y += delta.y;

        context.window->setPosition(position);
    }

    void setSize(Runtime::Context& context, const Vector2i& dimensions){

        context.window->setSize(dimensions);
    }

    void resize(Runtime::Context& context, const Vector2i& delta){

        Vector2i size = context.window->getSize();

        size.x += delta.x;
        size.y += delta.y;

        context.window->setSize(size);
    }

    void setIcon(Runtime::Context& context, const std::string& source){

        std::filesystem::path src{source};

        context.window->setIcon(src);
    }

    Vector2i getSize(Runtime::Context& context){

        return context.window->getSize();
    }

    Vector2i getPosition(Runtime::Context& context){

        return context.window->getPosition();
    }

    std::string getTitle(Runtime::Context& context){

        return context.window->getTitle();
    }
}