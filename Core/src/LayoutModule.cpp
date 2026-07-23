#include "../Novella/Scripting/API/LayoutModule.hpp"
#include "../Novella/Scripting/API/ObjectModule.hpp"
#include "../Novella/Scripting/API/DebugModule.hpp"
#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/Scene/Handle.hpp"
#include "../Novella/Components/Traits/Layoutable.hpp"
#include "../Novella/Systems/Layout/LayoutSystem.hpp"
#include <string>

namespace Novella::NScript::Modules::Layout{

    void setWidth(Runtime::Context& context, Handle handle, double width){

        if(handle.generation == 0) return;

        auto* currentScene = context.scene->getCurrentScene();

        if(!currentScene) return;

        auto* layoutable = currentScene->getInterface<Traits::Layoutable>(handle);

        if(!layoutable){

            std::string objectName = Modules::Object::getName(context, handle);

            if(objectName.empty()) objectName = "NULL";

            return;
        }

        if(!std::isfinite(width) || !std::isfinite(width)) throw std::runtime_error("NovellaScript Runtime Error: Layout.setWidth() requires two finite integers");

        if(static_cast<int64_t>(width) > std::numeric_limits<int32_t>().max()) throw std::runtime_error("NovellaScript Runtime Error: Layout.setWidth() requires value to be representable as a 32 bit signed integer");
        
        Style style = layoutable->getStyle();

        style.widthMode = SizeMode::Fixed;
        style.width = static_cast<int32_t>(width);

        layoutable->setStyle(style);

        currentScene->markDirty();
    }

    void setHeight(Runtime::Context& context, Handle handle, double height){

        if(handle.generation == 0) return;

        auto* currentScene = context.scene->getCurrentScene();

        if(!currentScene) return;

        auto* layoutable = currentScene->getInterface<Traits::Layoutable>(handle);

        if(!layoutable){

            std::string objectName = Modules::Object::getName(context, handle);

            if(objectName.empty()) objectName = "NULL";

            return;
        }

        if(!std::isfinite(height) || !std::isfinite(height)) throw std::runtime_error("NovellaScript Runtime Error: Layout.setWidth() requires two finite integers");

        if(static_cast<int64_t>(height) > std::numeric_limits<int32_t>().max()) throw std::runtime_error("NovellaScript Runtime Error: Layout.setWidth() requires value to be representable as a 32 bit signed integer");

        Style style = layoutable->getStyle();

        style.heightMode = SizeMode::Fixed;
        style.height = static_cast<int32_t>(height);

        layoutable->setStyle(style);
        
        currentScene->markDirty();
          
    }

    void setSize(Runtime::Context& context, Handle handle, double width, double height){

        setWidth(context, handle,width);
        setHeight(context, handle,width);

    }

    double getWidth(Runtime::Context& context, Handle handle){

        if(handle.generation == 0) return 0;

        auto* currentScene = context.scene->getCurrentScene();

        if(!currentScene) return 0;

        auto* layoutable = currentScene->getInterface<Traits::Layoutable>(handle);

        if(!layoutable){

            std::string objectName = Modules::Object::getName(context, handle);

            if(objectName.empty()) objectName = "NULL";

            return 0;
        }

        return static_cast<double>(layoutable->getComputedRectangle().width);
    }

    double getHeight(Runtime::Context& context, Handle handle){

        if(handle.generation == 0) return 0;

        auto* currentScene = context.scene->getCurrentScene();

        if(!currentScene) return 0;

        auto* layoutable = currentScene->getInterface<Traits::Layoutable>(handle);

        if(!layoutable){

            std::string objectName = Modules::Object::getName(context, handle);

            if(objectName.empty()) objectName = "NULL";

            return 0;
        }

        return static_cast<double>(layoutable->getComputedRectangle().height);
        
    } 
}