#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Commands{

    void setMousePosition(CommandContext& context, const nlohmann::json& args);

    void showCursor(CommandContext& context, const nlohmann::json& args);

    void hideCursor(CommandContext& context, const nlohmann::json& args);

    void enableCursor(CommandContext& context, const nlohmann::json& args);
    
    void disableCursor(CommandContext& context, const nlohmann::json& args);
}