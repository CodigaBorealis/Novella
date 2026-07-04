#include "../Novella/Scripting/Interpreter/FunctionExecutor.hpp"
#include <vector>

namespace Novella::NScript::Runtime{

    void FunctionExecutor::setStatementEvaluator(StatementEvaluator& evaluator){

        this->statementEvaluator = &evaluator;
    }

    Parser::Value FunctionExecutor::call(const std::string& name, const std::vector<Parser::Value>& args){

        return {};
    }
}