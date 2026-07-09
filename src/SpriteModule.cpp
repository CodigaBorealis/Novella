#include "../Novella/Scripting/API/SpriteModule.hpp"
#include "../Novella/Scripting/API/DebugModule.hpp"
#include "../Novella/Components/Traits/Renderable.hpp"
#include "../Novella/Components/Primitives/Color.hpp"
#include "../Novella/Scripting/API/ObjectModule.hpp"
#include "../Novella/Scene/SceneManager.hpp"
#include <cmath>

namespace Novella::NScript::Modules::Sprite{

    void setTexture(Runtime::Context& context, Handle handle, const std::string& name){

        
    }
    
    void setTint(Runtime::Context& context, Handle handle, double r, double g, double b, double a){

        if(handle.generation == 0) return;

        auto* currentScene = context.scene->getCurrentScene();

        if(!currentScene) return;

        auto* renderable = currentScene->getInterface<Traits::Renderable>(handle);

        if(!renderable){

            std::string objectName = Modules::Object::getName(context, handle);

            if(objectName.empty()) objectName = "NULL";

            Debug::print(context, "NovellaScript Runtime Warning: Object '" + objectName + "' does not support Sprite.setColor()");

            return;
        }

        if(!std::isfinite(r) || std::floor(r) != r || r < 0) throw std::runtime_error("NovellaScript Runtime Error: Sprite.setTint() requires all numerical arguments to be positive integers");
        if(!std::isfinite(g) || std::floor(g) != g || g < 0) throw std::runtime_error("NovellaScript Runtime Error: Sprite.setTint() requires all numerical arguments to be positive integers");
        if(!std::isfinite(b) || std::floor(b) != b || b < 0) throw std::runtime_error("NovellaScript Runtime Error: Sprite.setTint() requires all numerical arguments to be positive integers");
        if(!std::isfinite(a) || std::floor(a) != a || a < 0) throw std::runtime_error("NovellaScript Runtime Error: Sprite.setTint() requires all numerical arguments to be positive integers");

        uint8_t red = static_cast<uint8_t>(r);
        uint8_t green = static_cast<uint8_t>(g);
        uint8_t blue = static_cast<uint8_t>(b);
        uint8_t alpha = static_cast<uint8_t>(a);

        if(red > 255 || green > 255 || blue > 255 || alpha > 255) throw std::runtime_error("NovellaScript Runtime Error: Renderer.setBackgroundColor() requires all arguments to be between 0 and 255");

        Color color{red, green, blue, alpha};

        renderable->setColor(color);

    }
    
    std::string getTexture(Runtime::Context& context, Handle handle){


    }
    

}