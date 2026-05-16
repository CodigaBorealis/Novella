#pragma once
#include <raylib.h>
#include <string>
#include "../../Math/Vector2x.hpp"
#include "../../Graphics/Color.hpp"

namespace Novella{

    class Window{

        public:

        Window() = delete;
        
        Window(const Window&) = delete;

        Window& operator=(const Window&) = delete;

        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        Window(int width, int height, const std::string& title, int targetFPS);
        
        ~Window();

        bool isOpen() const;

        void beginFrame() const;
        void endFrame() const;

        void clear(const Graphics::Color& color);

        void toggleFullscreen();
        bool isFullScreen() const;

        void toggleBorderLess();
        
        void minimize();
        bool isMinimized() const;

        void maximize();
        bool isMaximized() const;

        bool isFocused() const;

        void close();

        void setSize(const Math::Vector2i& dimensions);
        Math::Vector2i getSize() const;
        bool isResized() const;


        void setTitle(const std::string& title);
        const std::string& getTitle() const;

        void setTargetFPS(int fps);
        int getFPS() const;

        void setFlags(unsigned int flags);

        void create(int width, int height, const std::string& title, int targetFPS);
        private:

        std::string title;

    };
}
