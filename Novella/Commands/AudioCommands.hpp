#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Commands{

    void playSound(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void playMusic(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void stopSound(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void stopMusic(const std::string& target,CommandContext &context, const nlohmann::json &args);

}