#pragma once
#include <string>
#include "../../Core/Math/Vector2x.hpp"
namespace Novella{

    class Window;
}

namespace Novella::NScript{

    class WindowModule{

        public:
            
        WindowModule() = delete;

        WindowModule(Window& window)
            :
            window(window)
            {}
        
        void setTitle(const std::string& title);

        void setPosition(const Vector2i& position);

        void move(const Vector2i& delta);

        void setSize(const Vector2i& dimensions);

        void resize(const Vector2i& delta);

        void setIcon(const std::string& resource);

        Vector2i getSize() const;

        Vector2i getPosition() const;

        std::string getTitle() const;

        private:

        Window& window;
    };
}