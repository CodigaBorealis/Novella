#pragma once
#include <raylib.h>
#include <string>
#include <filesystem>
#include "../Math/Vector2x.hpp"
#include "../Graphics/Color.hpp"
#include "WindowFlags.hpp"
namespace Novella{

    class Window{

        public:

        Window() = delete;
        
        Window(const Window&) = delete;

        Window& operator=(const Window&) = delete;

        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        Window(int width, int height, const std::string& title, int targetFPS);

        Window(int width, int height, const std::string& title, int targetFPS, WindowFlags flags);

        Window(int width, int height, const std::string& title, int targetFPS,const std::filesystem::path& icon);

        Window(int width, int height, const std::string& title, int targetFPS,const std::filesystem::path& icon, WindowFlags flags);
        
        bool isOpen() const;

        void clear(const Graphics::Color& color);

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

        void setSize(const Math::Vector2i& dimensions);
        Math::Vector2i getSize() const;
        bool isResized() const;


        void setTitle(const std::string& title);
        const std::string& getTitle() const;

        void setTargetFPS(int fps);
        int getFPS() const;

        void setFlags(WindowFlags flags);

        void create();
        
        private:

        std::string title;

    };
}
