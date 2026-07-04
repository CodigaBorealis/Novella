#include "../Novella/Scripting/API/WindowModule.hpp"
#include "../Novella/Windowing/Window.hpp"
#include <stdexcept>
#include "../Novella/Scripting/Interpreter/RuntimeEnvironment.hpp"
#include "../Novella/Utils/FileSystem.hpp"

namespace Novella::NScript::Modules::Window{

    void setTitle(Runtime::Context& context, const std::string& title){

        context.window->setTitle(title);
    }

    void setPositionX(Runtime::Context& context, double value){

        int x = static_cast<int>(value);

        if(x < 0) throw std::runtime_error("setPositionX: Can't move window X axis to a negative coordinate");

        context.window->setPosition({x, context.window->getPosition().y});
    }

    void setPositionY(Runtime::Context& context, double value){

        int y = static_cast<int>(value);

        if(y < 0) throw std::runtime_error("setPositionX: Can't move window Y axis to a negative coordinate");

        context.window->setPosition({context.window->getPosition().x, y});
    }

    void setWidth(Runtime::Context& context, double width){

        int castedWidth = static_cast<int>(width);

        if(castedWidth < 0) throw std::runtime_error("setWidth: Can't set window width to a negative value");

        context.window->setSize({castedWidth,context.window->getSize().y});
    }

    void setHeight(Runtime::Context& context, double height){

        int castedHeight = static_cast<int>(height);

        if(castedHeight < 0) throw std::runtime_error("setWidth: Can't set window width to a negative value");

        context.window->setSize({context.window->getSize().x, castedHeight});
    }

    void setIcon(Runtime::Context& context, const std::string& resource){

        if(!Utils::Filesystem::exists({resource})) throw std::runtime_error("setIcon: file not found: " + resource);

        context.window->setIcon(resource);
    }
        
    double getWidth(Runtime::Context& context){

        return context.window->getSize().x;
    }

    double getHeight(Runtime::Context& context){

        return context.window->getSize().y;
    }

    double getPositionX(Runtime::Context& context){

        return context.window->getPosition().x;
    }

    double getPositionY(Runtime::Context& context){

        return context.window->getPosition().y;
    }

    std::string getTitle(Runtime::Context& context){

        return context.window->getTitle();
    }
}