#include "../Novella/Scripting/API/SceneModule.hpp"
#include "../Novella/Scene/SceneManager.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>

namespace Novella::NScript::Modules::Scene{

    void load(Runtime::Context& context,const std::string& name){

        
    }

    void reload(Runtime::Context& context){

        
    }

    double objectCount(Runtime::Context& context){

        auto* currentScene = context.scene->getCurrentScene();

        if(!currentScene) return 0;


        return static_cast<float>(context.scene->getCurrentScene()->objectCount());
    }

    void reset(Runtime::Context& context){

        auto* scene = context.scene->getCurrentScene();

        if(!scene) return;

        //context.scene.reload();
    }
}