#include "../Novella/Window/Window.hpp"
#include "../Novella/Graphics/Color.hpp"
#include <raylib.h>
#include <stdexcept>

namespace Novella{

    Window::Window(int width, int height, const std::string& title, int targetFPS){
        
        if(::IsWindowReady()) return;

        ::InitWindow(width, height, title.c_str());

        ::SetTargetFPS(targetFPS);

        this->title = title;
    }

    Window::~Window(){

        if(::IsWindowReady()){

            ::CloseWindow();

        }
    }

    bool Window::isOpen() const{

        return ::IsWindowReady() && !::WindowShouldClose();
    }

    void Window::clear(const Graphics::Color& color){

        ::ClearBackground(color);
    }

    void Window::toggleFullscreen(){

        ::ToggleFullscreen();
    }

    bool Window::isFullScreen() const{

        return ::IsWindowFullscreen();
    }

    void Window::toggleBorderLess(){

        ::ToggleBorderlessWindowed();
    }

    void Window::minimize(){

        ::MinimizeWindow();
    }

    bool Window::isMinimized() const{

        return ::IsWindowMinimized();
    }

    void Window::maximize(){

        ::MaximizeWindow();
    }

    bool Window::isMaximized() const{

        return ::IsWindowMaximized();
    }

    bool Window::isFocused() const{

        return ::IsWindowFocused();
    }

    void Window::setSize(const Math::Vector2i& dimensions){

        SetWindowSize(dimensions.x, dimensions.y);
    }

    Math::Vector2i Window::getSize() const{

        return{GetScreenWidth(), GetScreenHeight()};
    }

    bool Window::isResized() const{

        return ::IsWindowResized();
    }

    void Window::setTitle(const std::string& title){

        ::SetWindowTitle(title.c_str());

        this->title = title;
    }

    const std::string& Window::getTitle() const{

        return title;
    }

    void Window::close(){

        if(::IsWindowReady()){

            ::CloseWindow();
        }

    }
    

    void Window::setTargetFPS(int fps){

        ::SetTargetFPS(fps);
    }
    
    int Window::getFPS() const{

        return ::GetFPS();
    }

    void Window::setFlags(unsigned int flags){

        if(IsWindowReady()) throw std::runtime_error("Window flags must be set before initialization");
        
        ::SetConfigFlags(flags);
    }

    
}