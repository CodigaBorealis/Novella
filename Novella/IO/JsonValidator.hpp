#pragma once
#include <nlohmann/json.hpp>
#include <string>

namespace Novella::IO::JsonValidator {

    bool validateScene(const nlohmann::json& data);
    bool validateObject(const std::string& type, const nlohmann::json& props);
    bool validateBinds(const nlohmann::json& props);
    bool validateVector(const nlohmann::json& props, const std::string& key);

}