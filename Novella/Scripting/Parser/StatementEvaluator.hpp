#pragma once
#include "Statement.hpp"
#include "ExpressionEvaluator.hpp"
#include <vector>

namespace Novella::NScript::Runtime{

    class RuntimeEnvironment;

}

namespace Novella::NScript::Parser{

    struct Script;

    class StatementEvaluator{

        public:

        StatementEvaluator() = delete;

        StatementEvaluator(Runtime::RuntimeEnvironment& runtime)
            :
            runtime(runtime),
            expressionEvaluator(runtime)
            {} 

        void execute(const Statement& statement) const;
        
        void execute(const Script& script) const;

        void execute(const std::vector<Statement>& statements) const;

        private:

        Runtime::RuntimeEnvironment& runtime;

        ExpressionEvaluator expressionEvaluator;
    };

}