#include "../Novella/Scripting/API/ObjectModule.hpp"
#include "../Novella/Scene/SceneManager.hpp"
#include <raylib.h>
#include "../Novella/Scripting/API/DebugModule.hpp"

namespace Novella::NScript::Modules::Object{

    Handle get(Runtime::Context& context, const std::string& name){
        
        auto* currentScene = context.scene->getCurrentScene();

        if(!currentScene){

            Debug::print(context, "NovellaScript Runtime Warning: No active scene to fetch '" + name + "'");

            return{};
        }

        Handle handle = currentScene->getObjectHandle(name);

        if(handle.generation == 0){

            Debug::print(context, "NovellaScript Runtime Warning: Could not find Object '" + name + "' in the scene");
        }

        return handle;
    }

    void destroy(Runtime::Context& context, Handle handle){

        if(handle.generation == 0) return;
        
        auto* currentScene = context.scene->getCurrentScene();

        if(!currentScene) return;

        currentScene->removeObject(handle);
    }

    bool exists(Runtime::Context& context, Handle handle){

        return getName(context, handle) != "";
    }

    std::string getName(Runtime::Context& context, Handle handle){

        if(handle.generation == 0) return "";

        auto* currentScene = context.scene->getCurrentScene();

        if(!currentScene) return "";

        auto name = currentScene->findName(handle);

        if(!name){

            Debug::print(context, "NovellaScript Runtime Warning: Object has already been destroyed or does not exist");

            return "";
        }

        return name.value();
    }
}