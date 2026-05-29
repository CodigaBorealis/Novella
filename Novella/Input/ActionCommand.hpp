#pragma once
#include <nlohmann/json.hpp>
#include <cstdint>
#include "../Commands/Alias.hpp"
namespace Novella::Input{

    struct ActionCommand{

        ActionCommand() = delete;

        ActionCommand(Alias alias, const nlohmann::json& args, uint64_t targetID)
            :
            alias(alias),
            args(args),
            targetID(targetID)
            {};

        Alias alias;
        nlohmann::json args;
        uint64_t targetID;
    };

}