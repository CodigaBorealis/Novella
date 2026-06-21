#include "../Novella/Scripting/API/WindowModule.hpp"
#include "../Novella/Windowing/Window.hpp"
#include <filesystem>

namespace Novella::NScript{

    void WindowModule::setTitle(const std::string& title){

        window.setTitle(title);
    }

    void WindowModule::setPosition(const Vector2i& position){

        window.setPosition(position);
    }

    void WindowModule::move(const Vector2i& delta){
    
        Vector2i position = window.getPosition();

        position.x += delta.x;
        position.y += delta.y;

        window.setPosition(position);
    }

    void WindowModule::setSize(const Vector2i& dimensions){

        window.setSize(dimensions);
    }

    void WindowModule::resize(const Vector2i& delta){

        Vector2i size = window.getSize();

        size.x += delta.x;
        size.y += delta.y;

        window.setSize(size);
    }

    void WindowModule::setIcon(const std::string& source){

        std::filesystem::path src{source};

        window.setIcon(src);
    }

    Vector2i WindowModule::getSize() const{

        return window.getSize();
    }

    Vector2i WindowModule::getPosition() const{

        return window.getPosition();
    }

    std::string WindowModule::getTitle() const{

        return window.getTitle();
    }
}