#include "../Novella/Components/Button.hpp"
#include <nlohmann/json.hpp>

namespace Novella::Components{

    Button::Button(const std::string& id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout)
        :
        Attribute::Object(id, Type::Button),
        texture(texture),
        Attribute::Layoutable(layout)
        {}
    
    Button::Button(const std::string& id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout, int renderLayer)
        :
        Attribute::Object(id, Type::Button),
        texture(texture),
        Attribute::Layoutable(layout),
        rLayer(renderLayer)
        {}

    const std::string& Button::getID() const{

        return this->id;
    }

    void Button::setID(const std::string& id){

        this->id = id;
    }

    nlohmann::json Button::serialize() const{

        return {};
    }

    const std::string& Button::getType() const{

        return this->type;
    }
            
    bool Button::contains(const Math::Vector2f& mousePos) const{

        return mousePos.x >= computedRectangle.x && mousePos.x <= computedRectangle.x + computedRectangle.width &&
               mousePos.y >= computedRectangle.y && mousePos.y <= computedRectangle.y + computedRectangle.height;

    }
/*
    void Button::setLabel(Label* label){

        this->label = label;
    }

    Label* Button::getLabel() const{

        if(this->label == nullptr) throw std::runtime_error("Label for this button is null: " + id);

        return label;
    }

    Label* Button::getLabel(){

        if(this->label == nullptr) throw std::runtime_error("Label for this button is null: " + id);

        return label;
    }
*/
    void Button::draw(Rendering::Renderer& renderer){

        renderer.drawTexture(*texture, computedRectangle, rotation, tint);
    }

    void Button::setRenderLayer(int layer){

        this->rLayer = layer;
    }
    int Button::renderLayer() const{

        return this->rLayer;
    }

    void Button::setColor(const Graphics::Color& color){

        this->tint = color;
    }

    const Graphics::Color& Button::getColor() const{

        return this->tint;
    }
        
    void Button::setRotation(float degrees){

        this->rotation = degrees;
    }
            
    float Button::getRotation() const{

        return this->rotation;
    }



}