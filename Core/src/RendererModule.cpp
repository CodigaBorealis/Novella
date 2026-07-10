#include "../Novella/Scripting/API/RendererModule.hpp"
#include "../Novella/Systems/Renderer/Renderer.hpp"
#include "../Novella/Components/Primitives/Color.hpp"
#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/Components/Traits/Layoutable.hpp"
#include "../Novella/Scripting/API/ObjectModule.hpp"
#include "../Novella/Scripting/API/DebugModule.hpp"

namespace Novella::NScript::Modules::Renderer{

    void setBackgroundColor(Runtime::Context& context, double r, double g, double b, double a){

        if(!std::isfinite(r) || std::floor(r) != r || r < 0) throw std::runtime_error("NovellaScript Runtime Error: Renderer.setBackgroundColor() requires all arguments to be positive integers");
        if(!std::isfinite(g) || std::floor(g) != g || g < 0) throw std::runtime_error("NovellaScript Runtime Error: Renderer.setBackgroundColor() requires all arguments to be positive integers");
        if(!std::isfinite(b) || std::floor(b) != b || b < 0) throw std::runtime_error("NovellaScript Runtime Error: Renderer.setBackgroundColor() requires all arguments to be positive integers");
        if(!std::isfinite(a) || std::floor(a) != a || a < 0) throw std::runtime_error("NovellaScript Runtime Error: Renderer.setBackgroundColor() requires all arguments to be positive integers");

        uint8_t red = static_cast<uint8_t>(r);
        uint8_t green = static_cast<uint8_t>(g);
        uint8_t blue = static_cast<uint8_t>(b);
        uint8_t alpha = static_cast<uint8_t>(a);

        if(red > 255 || green > 255 || blue > 255 || alpha > 255) throw std::runtime_error("NovellaScript Runtime Error: Renderer.setBackgroundColor() requires all arguments to be between 0 and 255");

        Color color{red, green, blue, alpha};

        context.renderer->setBackgroundColor(color);
    }
}