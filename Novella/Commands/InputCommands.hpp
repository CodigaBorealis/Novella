#pragma once
#include <nlohmann/json_fwd.hpp>
#include "CommandContext.hpp"
#include <raylib.h>

namespace Novella::Commands{

    void setMousePosition(CommandContext& context, const nlohmann::json& args);

    void ShowCursor();

    void HideCursor();

    void enableCursor();
    
    void disableCursor();
}