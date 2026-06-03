#include "../Novella/Commands/SceneCommands.hpp"
#include "../Novella/Commands/CommandContext.hpp"

namespace Novella::Commands{
    //Nothing for now because this depend on the sceneGraph which isnt restored yet
    void changeScene(const std::string& target,CommandContext &context, const nlohmann::json &args){


    }

    void spawnObject(const std::string& target,CommandContext &context, const nlohmann::json &args){


    }

    void RemoveObject(const std::string& target,CommandContext &context, const nlohmann::json &args){


    }
}