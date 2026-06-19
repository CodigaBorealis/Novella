#include "../Novella/Syntax/NovellaScript/Interpreter/StatementEvaluator.hpp"
#include "../Novella/Syntax/NovellaScript/Script.hpp"
#include "../Novella/Syntax/NovellaScript/Definition.hpp"
#include <variant>
#include <vector>

namespace Novella::Syntax::NovellaScript{

    void StatementEvaluator::execute(const std::vector<Statement>& statements) const{
        
        for(const auto& statement : statements){

            execute(statement);
        }
    }

    void StatementEvaluator::execute(const Statement& statement) const{
        
        if(auto expressionStatement = std::get_if<ExpressionStatement>(&statement)){

            expressionEvaluator.evaluate(expressionStatement->expression);
        }
    }

    void StatementEvaluator::execute(const Script& script) const{
        
        for(const auto& definition : script.definitions){

            if(std::holds_alternative<FunctionDefinition>(definition)){

                execute(std::get<FunctionDefinition>(definition).body);
            }
        }
    }
}
