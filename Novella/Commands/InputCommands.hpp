#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Commands{

    void setMousePosition(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void showCursor(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void hideCursor(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void enableCursor(uint64_t target,CommandContext &context, const nlohmann::json &args);
    
    void disableCursor(uint64_t target,CommandContext &context, const nlohmann::json &args);
}