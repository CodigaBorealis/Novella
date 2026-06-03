#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Commands{

    void setMousePosition(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void showCursor(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void hideCursor(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void enableCursor(const std::string& target,CommandContext &context, const nlohmann::json &args);
    
    void disableCursor(const std::string& target,CommandContext &context, const nlohmann::json &args);
}