#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Commands{

    void setMousePosition(CommandContext& context, const nlohmann::json& args);

    void ShowCursor();

    void HideCursor();

    void enableCursor();
    
    void disableCursor();
}