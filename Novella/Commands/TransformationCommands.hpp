#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;
}

namespace Novella::Components{

    class Object;    
};

namespace Novella::Commands{

    void resize(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void move(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void setPosition(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void setColor(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void setTransparency(uint64_t target,CommandContext &context, const nlohmann::json &args);

    void setText(uint64_t target,CommandContext &context, const nlohmann::json &args);
}