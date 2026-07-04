#include "../Novella/Scripting/API/SceneModule.hpp"
#include "../Novella/Scene/SceneManager.hpp"
#include <stdexcept>
#include <string>

namespace Novella::NScript::Modules::Scene{

    const Handle& getHandle(Runtime::Context& context, const std::string& name){

        auto& handle = context.scene->getCurrentScene()->getObjectHandle(name);

        return handle;
    }

    void destroy(Runtime::Context& context, const Handle& handle){

        auto* object = context.scene->getCurrentScene()->getObjectBase(handle);

        if(!object) throw std::runtime_error("This object has already been deleted, handle : " + std::to_string(handle.index));

        context.scene->getCurrentScene()->removeObject(handle);
    }

    void setPosition(Runtime::Context& context, const Handle& handle, Vector2d& positione){


    }
}