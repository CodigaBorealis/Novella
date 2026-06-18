#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Commands{

    void showMessage(const std::string& target,CommandContext &context, const nlohmann::json &args);

}