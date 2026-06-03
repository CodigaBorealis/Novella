#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Components{

    class Object;    
};

namespace Novella::Commands{

    void resize(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void move(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void setPosition(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void setColor(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void setTransparency(const std::string& target,CommandContext &context, const nlohmann::json &args);

    void setText(const std::string& target,CommandContext &context, const nlohmann::json &args);
}