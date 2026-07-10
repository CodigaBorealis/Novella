#pragma once
#include <string>
#include <variant>
#include <vector>
#include "Statement.hpp"
namespace Novella::NScript::Parser{

    struct FunctionDefinition{

        std::string name;
        std::vector<std::string> parameters;
        std::vector<Statement> body;
    };
}