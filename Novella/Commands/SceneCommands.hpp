#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Commands{

    void changeScene(CommandContext& context, const nlohmann::json& args);

    void spawnObject(CommandContext& context, const nlohmann::json& args);

    void RemoveObject(CommandContext& context, const nlohmann::json& args);

}