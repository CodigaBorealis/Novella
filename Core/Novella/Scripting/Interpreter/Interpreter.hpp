#pragma once
#include <variant>
#include <vector>
#include "FunctionExecutor.hpp"
#include "RuntimeContext.hpp"
#include "RuntimeEnvironment.hpp"
#include "ExpressionEvaluator.hpp"
#include "../Parser/Expression.hpp"

namespace Novella::Input{

    enum class Key;
}
namespace Novella::Input::Mouse{

    enum class Button;
}

namespace Novella{

    class InteractionSystem;

    struct KeyboardEvent;

    struct MouseEvent;
}

namespace Novella::NScene::Parser{

    struct ScriptDefinition;
    struct Script;
}

namespace Novella{

    class Engine;
}

namespace Novella::NScript::Runtime{

    class Interpreter{
                
        public:

        Interpreter():
        expressionEvaluator(runtime),
        statementEvaluator(runtime){

            expressionEvaluator.setFunctionExecutor(functionExecutor);
            statementEvaluator.setExpressionEvaluator(expressionEvaluator);
            functionExecutor.setStatementEvaluator(statementEvaluator);
            functionExecutor.setRuntime(runtime);
        }

        using RunTimeValue = std::variant<std::monostate, double, bool, std::string, char, std::vector<Parser::Expression>>;

        void loadScript(const Parser::Script& definition);

        void clear();
        
        void initialize(Engine& engine);

        void run();
        
        Context& runtimeContext();

        private:
            
        RuntimeEnvironment runtime;
        ExpressionEvaluator expressionEvaluator;
        StatementEvaluator statementEvaluator;
        FunctionExecutor functionExecutor;

        RunTimeValue callFunction(const std::string& moduleName, const std::string& functionName, const std::vector<RunTimeValue>& args = {});

        std::string getFunctionName(const Parser::Expression* answer);
        void executeStatements(const std::vector<Parser::Statement>& statements);
        void executeStatement(const Parser::Statement& statement);
    };

}