#include "../Novella/Components/UI/Label.hpp"
#include "../Novella/Systems/Layout/LayoutSystem.hpp"
#include <raylib.h>

namespace Novella::UI{

    Label::Label(std::shared_ptr<Font> font, const std::string& text){

        setFont(font);
        setText(text);
    }

    Label::Label(std::shared_ptr<Font> font, int size, const std::string& text, const Style& style, int renderLayer){

        setFont(font);
        setFontSize(size);
        setText(text);
        setStyle(style);
        setRenderLayer(renderLayer);
    }
        
        
    void Label::draw(Renderer& renderer){

        renderer.drawFont(*getFont(), getText(), getComputedRectangle(), getFontSize(), getSpacing(), getColor());
    }

    //Must hook it into the loop somehow
    void Label::computeSize(const Vector2i& parentSize){

        Vector2f textSize {::MeasureTextEx(getFont()->getHandle(), getText().c_str(), float(getFontSize()), getSpacing())};

        setComputedRectangle(LayoutSystem::computeLabel(getStyle(), textSize, parentSize));
    }
}