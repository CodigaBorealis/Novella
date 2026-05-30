#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Commands{

    void changeScene(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void spawnObject(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void RemoveObject(uint64_t target,CommandContext &context, const nlohmann::json &args);

}