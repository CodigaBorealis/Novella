#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Commands{

    void playSound(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void playMusic(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void stopSound(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void stopMusic(uint64_t target,CommandContext &context, const nlohmann::json &args);

}