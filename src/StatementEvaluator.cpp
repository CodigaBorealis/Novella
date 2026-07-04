#include "../Novella/Scripting/Interpreter/ExpressionEvaluator.hpp"
#include "../Novella/Scripting/Interpreter/StatementEvaluator.hpp"
#include "../Novella/Scripting/Interpreter/RuntimeEnvironment.hpp"
#include "../Novella/Scripting/Parser/Definition.hpp"
#include <variant>
#include <vector>
#include <iostream>

namespace Novella::NScript::Runtime{

    void StatementEvaluator::setExpressionEvaluator(ExpressionEvaluator& evaluator){

        this->expressionEvaluator = &evaluator;
    }

    void StatementEvaluator::execute(const Parser::Expression& expression) const{

        auto value= expressionEvaluator->evaluate(expression);

    };

    void StatementEvaluator::execute(const std::vector<Parser::Statement>& statements) const{
        
        for(const auto& statement : statements){

            execute(statement);
        }
    }

    void StatementEvaluator::execute(const Parser::Statement& statement) const{
        
        std::cout << "REACHED EXECUTE BUT IS NOT A EXPRESSION STATEMENT\n";

        if(auto expressionStatement = std::get_if<Parser::ExpressionStatement>(&statement)){

            std::cout << "EVALUATING\n";

            expressionEvaluator->evaluate(expressionStatement->expression);
        }
    }
}
