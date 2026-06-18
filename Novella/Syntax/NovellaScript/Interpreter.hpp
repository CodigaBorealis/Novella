#pragma once
#include "Script.hpp"
#include "../../Input/CommandDispatcher.hpp"
#include <unordered_map>
#include <variant>
#include <tuple>
#include <vector>

namespace Novella::Syntax::NovellaScript{

    class Interpreter{

        public:
        
        using RunTimeValue = std::variant<std::monostate, double, bool, std::string, char, std::vector<Expression>>;

        Interpreter() = delete;

        explicit Interpreter(Input::CommandDispatcher& dispatcher);

        RunTimeValue callFunction(const std::string& moduleName, const std::string& functionName, const std::vector<RunTimeValue>& args = {});

        private:
        
        std::string getFunctionName(const Expression* answer);
        void executeStatement(const Statement& statement);

        RunTimeValue evaluateExpression(const Expression& expression);

        void resolveImports();

        Input::CommandDispatcher& dispatcher;
        std::vector<Script> scripts;

        std::unordered_map<std::string, std::unordered_map<std::string, RunTimeValue>> persistentStorage;
        std::unordered_map<std::string, RunTimeValue> localScope;
    };

}