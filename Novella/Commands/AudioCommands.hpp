#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Commands{

    void playSound(CommandContext& context, const nlohmann::json& args);

    void playMusic(CommandContext& context, const nlohmann::json& args);

    void stopSound(CommandContext& context, const nlohmann::json& args);

    void stopMusic(CommandContext& context, const nlohmann::json& args);

}