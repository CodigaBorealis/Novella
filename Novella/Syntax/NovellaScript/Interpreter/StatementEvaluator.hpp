#pragma once
#include "../Statement.hpp"
#include "ExpressionEvaluator.hpp"
#include <vector>

namespace Novella::Syntax::NovellaScript{

    struct Script;
    class RuntimeEnvironment;

    class StatementEvaluator{

        public:

        StatementEvaluator() = delete;

        StatementEvaluator(RuntimeEnvironment& runtime)
            :
            runtime(runtime),
            expressionEvaluator(runtime)
            {} 

        void execute(const Statement& statement) const;
        
        void execute(const Script& script) const;

        void execute(const std::vector<Statement>& statements) const;

        private:

        RuntimeEnvironment& runtime;

        ExpressionEvaluator expressionEvaluator;
    };

}