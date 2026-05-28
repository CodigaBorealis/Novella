#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <cstdint>

namespace Novella::Input{

    enum class Target : uint64_t;

    struct ActionCommand{

        ActionCommand() = delete;

        ActionCommand(const std::string& name, const nlohmann::json& args, Target target)
            :
            name(name),
            args(args),
            target(target)
            {};

        std::string name;
        nlohmann::json args;
        Target target;
    };

}