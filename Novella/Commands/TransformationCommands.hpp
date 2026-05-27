#pragma once
#include "CommandContext.hpp"
#include <nlohmann/json_fwd.hpp>
namespace Novella::Commands{

    void resize(CommandContext& context, Attribute::Object& object, const nlohmann::json& args);

    void move(CommandContext& context, Attribute::Object& object, const nlohmann::json& args);

    void setPosition(CommandContext& context, Attribute::Object& object, const nlohmann::json& args);

    void setColor(CommandContext& context, Attribute::Object& object, const nlohmann::json& args);

    void setTransparency(CommandContext& context, Attribute::Object& object, const nlohmann::json &args);

    void setText(CommandContext& context, Attribute::Object& object, const nlohmann::json &args);
}