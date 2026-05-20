#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace Novella::Input{

    struct ActionCommand{

        std::string name;
        nlohmann::json args;
        std::string target;
    };

}