#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Commands{

    void changeScene(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void spawnObject(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void RemoveObject(const std::string& target,CommandContext &context, const nlohmann::json &args);

}