#pragma once
#include "WindowFlags.hpp"
#include <raylib.h>
#include <string>
#include <filesystem>
#include "../Core/Math/Vector2x.hpp"
#include "../Components/Primitives/Color.hpp"
namespace Novella{

    enum class WindowFlags : unsigned int;

}

namespace Novella::Graphics {

    class Color;

}

namespace Novella{

    class Window{

        public:

        ~Window();
        
        Window() = delete;
        
        Window(const Window&) = delete;

        Window& operator=(const Window&) = delete;

        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        Window(int width, int height, const std::string& title, int targetFPS,const std::filesystem::path& icon, WindowFlags flags);
        
        bool hasWindowFlag(WindowFlags flags);

        bool isOpen() const;

        void toggleFullscreen();
        bool isFullScreen() const;

        void toggleBorderLess();
        
        void minimize();
        bool isMinimized() const;

        void maximize();
        bool isMaximized() const;

        void setIcon(const std::filesystem::path& file);

        bool isFocused() const;

        void close();

        void setSize(const Vector2i& dimensions);
        Vector2i getSize() const;
        bool isResized() const;


        void setTitle(const std::string& title);
        const std::string& getTitle() const;

        void setTargetFPS(int fps);
        int getFPS() const;

        void setFlags(WindowFlags flags);

        void create();
        
        void setPosition(const Vector2i& position);
        Vector2i getPosition() const;
        
        private:

        bool requestedClose = false;
        std::string title;
    };
}
