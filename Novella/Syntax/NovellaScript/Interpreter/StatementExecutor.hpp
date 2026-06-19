#pragma once
#include "../Statement.hpp"
#include <vector>
#include <optional>

namespace Novella::Syntax::NovellaScript{

    struct Script;

    class StatementExecutor{

        public:

        std::vector<Expression> evaluateExecOnce(const Script& script);

        std::vector<Expression> evaluateDefinitions(const Script& script);

        std::vector<Expression> evaluateStatements(const std::vector<Statement>& statements);

    };

}