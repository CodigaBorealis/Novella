#include "../Novella/Components/Label.hpp"
#include <raylib.h>
#include <stdexcept>
namespace Novella::Components{

    Label::Label(const std::string& id, std::shared_ptr<Graphics::Font> font, const Math::Vector2i& position, int size, const std::string& text)
        :
        id(id),
        font(font),
        position(position),
        size(size),
        text(text)
        {}

    Label::Label(const std::string& id, std::shared_ptr<Graphics::Font> font, const Math::Vector2i& position, int size, const std::string& text, int renderLayer)
        :
        id(id),
        font(font),
        position(position),
        size(size),
        rLayer(renderLayer)
        {}
        
        
    void Label::draw(Rendering::Renderer& renderer){

        renderer.drawFont(*font, text, position, size, spacing, tint);
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

    void Label::setPosition(const Math::Vector2i& position){

        this->position = position;
    };
    
    const Math::Vector2i& Label::getPosition() const{

        return this->position;
    };

    void Label::setSize(unsigned int size){

        this->size = size;
    };

    unsigned int Label::getSize() const{

        return this->size;
    };

    void Label::addMouseBind(Input::Mouse button, const std::string& name, const nlohmann::json& args, const std::string& target){

        if(mouseBinds.contains(button)) throw std::runtime_error("This label already has an action binded to this button");

        mouseBinds.emplace(button,BindedAction{name, args, target});
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

        return mousePos.x >= position.x && mousePos.x <= position.x + size.x &&
               mousePos.y >= position.y && mousePos.y <= position.y + size.y;

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

}