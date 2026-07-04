#pragma once
#include <string>
#include "../Parser/Expression.hpp"

namespace Novella::NScript::Runtime{

    class StatementEvaluator;

    class FunctionExecutor{

        public:

        FunctionExecutor() = default;

        void setStatementEvaluator(StatementEvaluator& evaluator);
        Parser::Value call(const std::string& name, const std::vector<Parser::Value>& args);

        private:

        StatementEvaluator* statementEvaluator;
    };
}