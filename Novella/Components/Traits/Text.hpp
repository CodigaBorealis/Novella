#pragma once
#include <memory>
#include "../Primitives/Font.hpp"
#include "../../Core/Math/Vector2x.hpp"

namespace Novella::Traits{

    struct Text{

        virtual ~Text() = default;
        
        virtual void computeSize(const Vector2i& parentSize) = 0;

        void setFontSize(unsigned int size){fontSize = size;}
        unsigned int getFontSize() const{return fontSize;}

        void setSpacing(float spacing){this->spacing = spacing;}

        float getSpacing() const{return spacing;}

        void setText(const std::string& text){this->text = text;}
        const std::string& getText() const{return text;}
        
        void setFont(std::shared_ptr<Font> font){this->font = font;}

        std::shared_ptr<Font> getFont() const{return font;}

        private:

        std::string text;
        std::shared_ptr<Font> font;
        int fontSize = 32;
        float spacing = 1.0f;
    };  
}
