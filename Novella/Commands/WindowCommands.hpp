#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Commands{

    void setWindowTitle(CommandContext& context, const nlohmann::json& args);

    void setWindowIcon(CommandContext& context, const nlohmann::json& args);

    void setWindowPosition(CommandContext& context, const nlohmann::json& args);

    void setWindowSize(CommandContext& context, const nlohmann::json& args);

    void closeWindow(CommandContext& context, const nlohmann::json& args);

}