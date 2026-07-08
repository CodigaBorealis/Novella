#pragma once
#include <string>
#include "../Parser/Expression.hpp"

namespace Novella::NScript::Runtime{

    class StatementEvaluator;
    class RuntimeEnvironment;

    class FunctionExecutor{

        public:

        FunctionExecutor() = default;

        void setStatementEvaluator(StatementEvaluator& evaluator);
        void setRuntime(RuntimeEnvironment& runtime);
        
        Parser::Value call(const std::string& name, const std::vector<Parser::Value>& args);

        private:

        struct CallFrameGuard{

            RuntimeEnvironment* runtime;
            CallFrameGuard(RuntimeEnvironment* runtime, const std::string& name);
            ~CallFrameGuard();
        };

        StatementEvaluator* statementEvaluator;
        RuntimeEnvironment* runtime;
    };
}