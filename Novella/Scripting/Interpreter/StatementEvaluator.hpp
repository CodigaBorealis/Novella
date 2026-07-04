#pragma once
#include <vector>
#include "../Parser/ScriptFwd.hpp"

namespace Novella::NScript::Parser {

    struct Script;
}

namespace Novella::NScript::Runtime{

    class RuntimeEnvironment;
    class ExpressionEvaluator;

    class StatementEvaluator{

        public:

        StatementEvaluator() = delete;

        StatementEvaluator(Runtime::RuntimeEnvironment& runtime)
            :
            runtime(runtime)
            {} 
        
        void setExpressionEvaluator(ExpressionEvaluator& evaluator);
        
        void execute(const Parser::Expression& expression) const;

        void execute(const Parser::Statement& statement) const;
        
        void execute(const std::vector<Parser::Statement>& statements) const;

        private:
        
        Runtime::RuntimeEnvironment& runtime;

        Runtime::ExpressionEvaluator* expressionEvaluator = nullptr;
    };

}