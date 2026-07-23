#include "../Novella/Scripting/API/TransformModule.hpp"
#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/Components/Traits/Layoutable.hpp"
#include "../Novella/Scripting/API/DebugModule.hpp"
#include "../Novella/Scripting/API/ObjectModule.hpp"
#include <cmath>
#include <cstdint>
#include <limits>
#include <stdexcept>

namespace Novella::NScript::Modules::Transform{
    
    void setRotation(Runtime::Context& context, Handle handle, double degrees){


    }

    void rotate(Runtime::Context& context, Handle handle,double delta){


    }

    void flipX(Runtime::Context& context, Handle handle){


    }

    void flipY(Runtime::Context& context, Handle handle){


    }


    void setPosition(Runtime::Context& context, Handle handle, double x, double y){


    }

    void setPositionX(Runtime::Context& context, Handle handle, double x){


    }

    void setPositionY(Runtime::Context& context, Handle handle, double y){


    }

    void move(Runtime::Context& context, Handle handle, double deltaX, double deltaY){

        if(handle.generation == 0) return;

        auto* currentScene = context.scene->getCurrentScene();

        if(!currentScene) return;

        auto* layoutable = currentScene->getInterface<Traits::Layoutable>(handle);

        if(!layoutable){

            std::string objectName = Modules::Object::getName(context, handle);

            if(objectName.empty()) objectName = "NULL";

            return;
        }

        if(!std::isfinite(deltaX) || !std::isfinite(deltaY)) throw std::runtime_error("NovellaScript Runtime Error: Transform.move() requires two finite integers");

        if(static_cast<int64_t>(deltaX) > std::numeric_limits<int32_t>().max() || static_cast<int64_t>(deltaY) > std::numeric_limits<std::int32_t>().max()){

            throw std::runtime_error("NovellaScript Runtime Error: Transform.move() requires both values to be representable as a 32 bit signed integer");
        }

        Style style = layoutable->getStyle();

        style.offset.x += static_cast<int32_t>(deltaX);
        style.offset.y += static_cast<int32_t>(deltaY);

        layoutable->setStyle(style);

        currentScene->markDirty();
    }


    double getX(Runtime::Context& context, Handle handle){

        return 0;
    }

    double getY(Runtime::Context& context, Handle handle){

        return 0;
    }


    double getRotation(Runtime::Context& context, Handle handle){

        return 0;
    }

}