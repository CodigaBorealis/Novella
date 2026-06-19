#include "../Novella/Syntax/NovellaScript/Interpreter/StatementExecutor.hpp"
#include "../Novella/Syntax/NovellaScript/Script.hpp"
#include "../Novella/Syntax/NovellaScript/Definition.hpp"
#include <iterator>
#include <variant>
#include <vector>

namespace Novella::Syntax::NovellaScript{

    std::vector<Expression> StatementExecutor::evaluateExecOnce(const Script& script){
        
        std::vector<Expression> resultingExpressions{};

        for(const auto& definition : script.definitions){

            if(std::holds_alternative<ModuleDefinition>(definition)){

                auto& module = std::get<ModuleDefinition>(definition);

                std::vector<Expression> execOnce = evaluateStatements(module.firstLoad);

                std::move(execOnce.begin(), execOnce.end(), std::back_inserter(resultingExpressions));
            }
        }

        return resultingExpressions;
    }

    std::vector<Expression> StatementExecutor::evaluateDefinitions(const Script& script){
        
        std::vector<Expression> resultingExpressions{};

        for(const auto& definition : script.definitions){

            if(std::holds_alternative<ModuleDefinition>(definition)){

                auto& module = std::get<ModuleDefinition>(definition);
                
                for(const auto & function : module.functions){

                    std::vector<Expression> functionBody = evaluateStatements(function.body);

                    std::move(functionBody.begin(), functionBody.end(), std::back_inserter(resultingExpressions));
                }
            }
        }

        return resultingExpressions;
    }

    std::vector<Expression> StatementExecutor::evaluateStatements(const std::vector<Statement>& statements){

        std::vector<Expression> resultingExpressions{};

        for(const auto& statement: statements){
            
            if(std::holds_alternative<ExpressionStatement>(statement)){

                auto& stmt = std::get<ExpressionStatement>(statement);

                resultingExpressions.push_back(stmt.expression);
            }
        }

        return resultingExpressions;
    }
}
