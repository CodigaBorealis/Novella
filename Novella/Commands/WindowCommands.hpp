#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Commands{

    void setWindowTitle(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void setWindowIcon(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void setWindowPosition(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void setWindowSize(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void closeWindow(const std::string& target,CommandContext &context, const nlohmann::json &args);

}