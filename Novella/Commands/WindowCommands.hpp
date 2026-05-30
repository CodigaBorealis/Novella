#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Commands{

    void setWindowTitle(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void setWindowIcon(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void setWindowPosition(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void setWindowSize(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void closeWindow(uint64_t target,CommandContext &context, const nlohmann::json &args);

}