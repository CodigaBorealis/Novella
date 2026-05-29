#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Components{

    class Object;    
};

namespace Novella::Commands{

    void resize(CommandContext& context, const nlohmann::json& args);

    void move(CommandContext& context, const nlohmann::json& args);

    void setPosition(CommandContext& context, const nlohmann::json& args);

    void setColor(CommandContext& context, const nlohmann::json& args);

    void setTransparency(CommandContext& context, const nlohmann::json& args);

    void setText(CommandContext& context, const nlohmann::json& args);
}