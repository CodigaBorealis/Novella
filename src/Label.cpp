#include "../Novella/Components/Label.hpp"
#include "../Novella/Layout/LayoutSystem.hpp"
#include <raylib.h>
#include <stdexcept>
namespace Novella::Components{

    Label::Label(const std::string& id, std::shared_ptr<Graphics::Font> font, int size, const std::string& text, const Layout& layout)
        :
        id(id),
        font(font),
        Attribute::Layoutable(layout),
        size(size),
        text(text)
        {}
//I'm stupid
    Label::Label(const std::string& id, std::shared_ptr<Graphics::Font> font, int size, const std::string& text, const Layout& layout, int renderLayer)
        :
        id(id),
        font(font),
        Attribute::Layoutable(layout),
        size(size),
        text(text),
        rLayer(renderLayer)
        {}
        
        
    void Label::draw(Rendering::Renderer& renderer){

        renderer.drawFont(*font, text, computedRectangle, size, spacing, tint);
    }

    int Label::renderLayer() const{

        return this->rLayer;
    };

    void Label::setColor(const Graphics::Color& color){

        this->tint = color;
    };
    const Graphics::Color& Label::getColor() const{

        return this->tint;
    };

    void Label::setSize(unsigned int size){

        this->size = size;
    };

    unsigned int Label::getSize() const{

        return this->size;
    };

    void Label::addMouseBind(const Input::Mouse::Button button, const Input::ActionCommand& command){

        if(mouseBinds.contains(button)) throw std::runtime_error(command.name + " could not be binded because this label already has an action for this mouse button");

        mouseBinds.emplace(button, command);
    };

    void Label::setSpacing(float spacing){

        this->spacing = spacing;
    };

    float Label::getSpacing() const{

        return this->spacing;
    }

    bool Label::contains(const Math::Vector2f& mousePos) const{


        Math::Vector2f size{

            ::MeasureTextEx(
            this->font->getHandle(),
            this->text.c_str(),
            this->size,
            this->spacing)
        };

        return mousePos.x >= computedRectangle.x && mousePos.x <= computedRectangle.x + size.x &&
               mousePos.y >= computedRectangle.y && mousePos.y <= computedRectangle.y + size.y;

    };

    const std::string& Label::getID() const{

        return this->id;
    };

    nlohmann::json Label::serialize() const{

        return {};
    }

    const std::string Label::getType() const{

        return this->TYPE;
    }

    void Label::setText(const std::string& text){

        this->text = text;
    }
    
    const std::string& Label::getText() const{

        return this->text;
    }
        
    void Label::setFont(std::shared_ptr<Graphics::Font> font){

        if(!font) throw std::runtime_error("Cannot set the font to nullptr");

        this->font = font;
    }

        std::shared_ptr<Graphics::Font> Label::getFont() const{

            return this->font;
        }
    //Must hook it into the loop somehow
    void Label::computeSize(const Math::Vector2i& parentSize){

        Math::Vector2f textSize {::MeasureTextEx(font->getHandle(), text.c_str(), float(size), spacing)};

        computedRectangle = LayoutSystem::computeLabel(layout, textSize, parentSize);
    }
}