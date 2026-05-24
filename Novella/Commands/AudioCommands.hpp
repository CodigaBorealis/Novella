#pragma once
#include "CommandContext.hpp"
#include <nlohmann/json_fwd.hpp>
namespace Novella::Commands{

    void playSound(CommandContext& context, const nlohmann::json& args);

    void setBGM(CommandContext& context, const nlohmann::json& args);

}