#pragma once
#include "Statement.hpp"
#include <vector>

namespace Novella::Syntax::NovellaScript{

    struct Script{
        
    using Statement = std::variant<ReturnStatement, IfStatement, VariableStatement, FunctionCallStatement, ExpressionStatement>;

    std::vector<Definition> definitions;

    };
}