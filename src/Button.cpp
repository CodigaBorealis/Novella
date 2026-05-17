#include "../Novella/Components/Button.hpp"
#include <stdexcept>

namespace Novella::Components{

    Button::Button(const std::string id, std::shared_ptr<Graphics::Texture> texture, const Math::Vector2i& position, const Math::Vector2i& dimensions)
        :
        id(id),
        texture(texture),
        position(position),
        dimensions(dimensions)
        {}

    Button::Button(const std::string id, std::shared_ptr<Graphics::Texture> texture, const Math::Vector2i& position, const Math::Vector2i& dimensions, int renderLayer)
        :
        id(id),
        texture(texture),
        position(position),
        dimensions(dimensions),
        rLayer(renderLayer)
        {}

    const std::string& Button::getID() const{

        return this->id;
    }

    nlohmann::json Button::serialize() const{

        return {};
    }

    const std::string Button::getType() const{

        return this->type;
    }

    void Button::setPosition(const Math::Vector2i& position){

        this->position = position;
    }

    const Math::Vector2i& Button::getPosition() const{

        return this->position;
    }

    void Button::addMouseBind(Input::Mouse button, const std::string& name, const nlohmann::json& args, const std::string& target){

        if(mouseBinds.contains(button)) throw std::runtime_error(name + " could not be binded because this label already has an action for this mouse button");

        mouseBinds.emplace(button, BindedAction{name, args, target});
    }
            
    bool Button::contains(const Math::Vector2f& mousePos) const{

        return mousePos.x >= position.x && mousePos.x <= position.x + dimensions.x &&
               mousePos.y >= position.y && mousePos.y <= position.y + dimensions.y;

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

        renderer.drawTexture(*texture, position, dimensions, rotation, tint);
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