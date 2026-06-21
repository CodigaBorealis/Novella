#include "../Novella/Components/UI/Label.hpp"
#include "../Novella/Systems/Layout/LayoutSystem.hpp"
#include <raylib.h>
#include <stdexcept>

namespace Novella::UI{

//I'm stupid
    Label::Label(std::shared_ptr<Font> font, int size, const std::string& text, const Style& style, int renderLayer)
        :
        font(font),
        Traits::Layoutable(style),
        size(size),
        text(text),
        rLayer(renderLayer)
        {}
        
        
    void Label::draw(Renderer& renderer){

        renderer.drawFont(*font, text, computedRectangle, size, spacing, tint);
    }

    int Label::renderLayer() const{

        return this->rLayer;
    };

    void Label::setColor(const Color& color){

        this->tint = color;
    };
    const Color& Label::getColor() const{

        return this->tint;
    };

    void Label::setSize(unsigned int size){

        this->size = size;
    };

    unsigned int Label::getSize() const{

        return this->size;
    };

    void Label::setSpacing(float spacing){

        this->spacing = spacing;
    };

    float Label::getSpacing() const{

        return this->spacing;
    }

    bool Label::contains(const Vector2f& mousePos) const{


        Vector2f size{

            ::MeasureTextEx(
            this->font->getHandle(),
            this->text.c_str(),
            this->size,
            this->spacing)
        };

        return mousePos.x >= computedRectangle.x && mousePos.x <= computedRectangle.x + size.x &&
               mousePos.y >= computedRectangle.y && mousePos.y <= computedRectangle.y + size.y;

    };

    void Label::setText(const std::string& text){

        this->text = text;
    }
    
    const std::string& Label::getText() const{

        return this->text;
    }
        
    void Label::setFont(std::shared_ptr<Font> font){

        if(!font) throw std::runtime_error("Cannot set the font to nullptr");

        this->font = font;
    }

        std::shared_ptr<Font> Label::getFont() const{

            return this->font;
        }
    //Must hook it into the loop somehow
    void Label::computeSize(const Vector2i& parentSize){

        Vector2f textSize {::MeasureTextEx(font->getHandle(), text.c_str(), float(size), spacing)};

        computedRectangle = LayoutSystem::computeLabel(style, textSize, parentSize);
    }
}