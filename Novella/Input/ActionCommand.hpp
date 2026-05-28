#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace Novella::Input{

    enum class Target : unsigned int;

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