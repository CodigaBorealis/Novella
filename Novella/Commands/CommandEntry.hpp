#pragma once
#include <functional>
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class CommandContext;

    using CommandFunction = std::function<void(uint64_t, CommandContext&, const nlohmann::json&)>;

    enum class Alias : unsigned int;

    struct CommandEntry{

        Alias alias;
        CommandFunction function;
    };
}