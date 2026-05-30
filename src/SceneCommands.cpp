#include "../Novella/Commands/SceneCommands.hpp"
#include "../Novella/Commands/CommandContext.hpp"

namespace Novella::Commands{
    //Nothing for now because this depend on the sceneGraph which isnt restored yet
    void changeScene(uint64_t target,CommandContext &context, const nlohmann::json &args){


    }

    void spawnObject(uint64_t target,CommandContext &context, const nlohmann::json &args){


    }

    void RemoveObject(uint64_t target,CommandContext &context, const nlohmann::json &args){


    }
}