#include "../Novella/Scripting/API/SceneModule.hpp"
#include "../Novella/Scene/SceneManager.hpp"
#include <cstdint>
#include <stdexcept>
#include <string>

namespace Novella::NScript{

    uint64_t SceneModule::getHandle(const std::string& name){

        uint64_t handle = sceneManager.getCurrentScene()->getObjectHandle(name);

        if(handle == 0) throw std::runtime_error("This object does not exist: " + name);

        return handle;
    }

    void SceneModule::destroy(uint64_t handle){

        auto* object = sceneManager.getCurrentScene()->getObject(handle);

        if(!object) throw std::runtime_error("This object has already been deleted, handle : " + std::to_string(handle));

        sceneManager.getCurrentScene()->removeObject(handle);
    }

    void SceneModule::setPosition(uint64_t handle, Vector2d& position){


    }
}