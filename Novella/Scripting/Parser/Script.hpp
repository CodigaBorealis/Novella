#pragma once
#include "ScriptFwd.hpp"
#include "Statement.hpp"
#include <vector>

namespace Novella::NScript::Parser{

    struct Script{
        
    using Statement = std::variant<ReturnStatement, IfStatement, VariableStatement, ExpressionStatement>;

    std::vector<Definition> definitions;

    };
}