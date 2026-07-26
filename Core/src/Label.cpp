#include "../Novella/Components/UI/Label.hpp"
#include "../Novella/Systems/Layout/LayoutSystem.hpp"
#include <libintl.h>
#include <raylib.h>
namespace Novella::UI{

    Label::Label(std::shared_ptr<Font> font, const std::string& text){

        setFont(font);
        setText(text);
    }

    Label::Label(std::shared_ptr<Font> font, const std::string& text, int size, const Style& style, int renderLayer){

        setFont(font);
        setFontSize(size);
        setText(text);
        setStyle(style);
        setRenderLayer(renderLayer);
    }
        
        
    void Label::draw(Renderer& renderer){

        renderer.drawFont(*getFont(), getText(), getComputedRectangle(), getFontSize(), getSpacing(), getColor());

        renderer.drawRectangle(getComputedRectangle(),Colors::Green);
    }

    const std::unordered_map<std::string, Label::PropertyDescriptor>& Label::properties() const{

        return {};
    }
    
    Rectangle Label::naturalSize() const{

        Vector2x<float> textSize = ::MeasureTextEx(getFont()->getHandle(), getText().c_str(), static_cast<float>(getFontSize()), getSpacing());

        return{0, 0, textSize.x, textSize.y};
    }

    void Label::updateLayout(LayoutSystem& layout, const Rectangle& parent){
            
        setComputedRectangle(layout.compute(getStyle(),parent, naturalSize()));
    }

    Vector2x<float> Label::measure(LayoutSystem& layout) const{

        return{::MeasureTextEx(getFont()->getHandle(), getText().c_str(), static_cast<float>(getFontSize()), getSpacing())};

        
    }
}   