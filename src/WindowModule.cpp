#include "../Novella/Scripting/API/WindowModule.hpp"
#include "../Novella/Windowing/Window.hpp"
#include <raylib.h>
#include <stdexcept>
#include "../Novella/Scripting/Interpreter/RuntimeEnvironment.hpp"
#include "../Novella/Utils/FileSystem.hpp"
#include "../Novella/Core/Math/Vector2x.hpp"

namespace Novella::NScript::Modules::Window{

    void center(Runtime::Context& context){

        int monitor = ::GetCurrentMonitor();

        Vector2i monitorPosition{::GetMonitorPosition(monitor)};

        int monitorWidth = ::GetMonitorWidth(monitor);
        int monitorHeight = ::GetMonitorHeight(monitor);

        int windowWidth = context.window->getSize().x;
        int windowHeight = context.window->getSize().y;

        ::SetWindowPosition(static_cast<int>(monitorPosition.x + (monitorWidth - windowWidth) / 2), static_cast<int>(monitorPosition.y + (monitorHeight - windowHeight) / 2));

    }

    void close(Runtime::Context& context){

        context.window->close();
    }

    void minimize(Runtime::Context& context){

        context.window->minimize();
    }

    void maximize(Runtime::Context& context){

        context.window->maximize();
    }


    bool isFullScreen(Runtime::Context& context){

        return context.window->isFullScreen();
    }

    bool isResizable(Runtime::Context& context){

        return context.window->hasWindowFlag(WindowFlags::Resizable);
    }

    bool isFocused(Runtime::Context& context){

        return context.window->isFocused();
    }

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

    void setPosition(Runtime::Context& context, double x, double y){

        int castedX = static_cast<int>(x);
        int castedY = static_cast<int>(y);

        if(castedX < 0 || castedY < 0) throw std::runtime_error("setWidth: Can't set window position to a negative coordinate");

        context.window->setPosition({castedX, castedY});

    }   

    void setWidth(Runtime::Context& context, double width){

        int castedWidth = static_cast<int>(width);

        if(castedWidth < 0) throw std::runtime_error("setWidth: Can't set window width to a negative value");

        context.window->setSize({castedWidth,context.window->getSize().y});
    }

    void setHeight(Runtime::Context& context, double height){

        int castedHeight = static_cast<int>(height);

        if(castedHeight < 0) throw std::runtime_error("setHeight: Can't set window width to a negative value");

        context.window->setSize({context.window->getSize().x, castedHeight});
    }

    void setSize(Runtime::Context& context, double width, double height){

        int castedWidth = static_cast<int>(width);
        int castedHeight = static_cast<int>(height);

        if(castedHeight < 0 || castedWidth < 0) throw std::runtime_error("setSize: Can't set window width to a negative value");

        context.window->setSize({castedHeight, castedWidth});

    }   

    void setIcon(Runtime::Context& context, const std::string& resource){

        if(!Utils::Filesystem::exists({resource})) throw std::runtime_error("setIcon: file not found: " + resource);

        Utils::Filesystem::getRelativePath(resource);

        std::filesystem::path resolvedResource = context.projectRoot / resource;

        context.window->setIcon(resolvedResource);
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