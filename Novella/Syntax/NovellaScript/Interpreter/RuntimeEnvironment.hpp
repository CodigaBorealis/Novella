#pragma once
#include <stack>
#include <unordered_map>
#include <vector>
#include "../Expression.hpp"
#include "StatementEvaluator.hpp"

namespace Novella::Syntax::NovellaScript{

    struct Script;

    class RuntimeEnvironment{

        struct CallFrame{

            std::string functionName;
            std::unordered_map<std::string, UnderlyingValue> locals;
        };

        public:

        RuntimeEnvironment() = delete;

        RuntimeEnvironment(StatementEvaluator& evaluator)
            :
            statementEvaluator(evaluator)
            {}

        void registerData(const Script& script);

        UnderlyingValue getVariable(const std::string& name) const;

        void setVariable(const std::string& name, const UnderlyingValue& value);

        void clear();

        UnderlyingValue invokeFunction(const std::string& name, const std::vector<UnderlyingValue>& arguments);

        private:

        StatementEvaluator& statementEvaluator;

        void registerFunction(const FunctionDefinition& definition);
        
        void createVariable(const std::string& name, const UnderlyingValue& value);

        std::unordered_map<std::string, UnderlyingValue> variables;
        std::unordered_map<std::string, FunctionDefinition> functions;
        std::unordered_map<std::string, ModuleDefinition> loadedModules;
        std::unordered_map<std::string, std::unordered_map<std::string, UnderlyingValue>> persistentStorage;

        std::stack<CallFrame> callStack;
    };

}