#include "../Novella/Scripting/Parser/StatementEvaluator.hpp"
#include "../Novella/Scripting/Parser/Script.hpp"
#include "../Novella/Scripting/Parser/Definition.hpp"
#include <variant>
#include <vector>
#include <iostream>

namespace Novella::NScript::Parser{

    void StatementEvaluator::execute(const std::vector<Statement>& statements) const{
        
        for(const auto& statement : statements){

            std::cout << "EXECUTING STATEMENTS\n";

            execute(statement);
        }
    }

    void StatementEvaluator::execute(const Statement& statement) const{
        
        std::cout << "REACHED EXECUTE BUT IS NOT A EXPRESSION STATEMENT\n";

        if(auto expressionStatement = std::get_if<ExpressionStatement>(&statement)){

            std::cout << "EVALUATING\n";

            //expressionEvaluator.evaluate(expressionStatement->expression);
        }
    }

    void StatementEvaluator::execute(const Script& script) const{
        
        for(const auto& definition : script.definitions){
            static int count = 0;

            std::cout << "TOTAL DEFINITIONS: " << ++count << "\n";
            if(std::holds_alternative<ModuleDefinition>(definition)){
                
                auto& module = std::get<ModuleDefinition>(definition);

                std::cout << "IS A MODULE\n";

                static int thingsInside = 0;

                for(const auto& function : module.functions){

                    std::cout << "FUNCTIONS : " << ++thingsInside << "n";
                    execute(function.body);
                }
            }
        }
    }
}
