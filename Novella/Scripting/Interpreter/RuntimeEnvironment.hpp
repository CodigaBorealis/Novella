#pragma once
#include <unordered_map>
#include <vector>
#include "../Parser/Expression.hpp"
#include "../Parser/StatementEvaluator.hpp"

namespace Novella::NScript::Parser{

    struct Script;

    class StatementEvaluator;

}

namespace Novella::NScript::Runtime{

    class RuntimeEnvironment{

        struct CallFrame{

            std::string functionName;
            std::unordered_map<std::string, Parser::Value> locals;
        };

        public:

        RuntimeEnvironment() = default;

        void registerData(const Parser::Script& script);

        Parser::Value getVariable(const std::string& name) const;

        void setVariable(const std::string& name, const Parser::Value& value);

        void clear();

        const Parser::FunctionDefinition& getFunction(const std::string& name);

        private:

        void registerFunction(const Parser::FunctionDefinition& definition);
        
        void createVariable(const std::string& name, const Parser::Value& value);

        std::unordered_map<std::string, Parser::Value> variables;
        std::unordered_map<std::string, Parser::FunctionDefinition> functions;
        std::unordered_map<std::string, Parser::ModuleDefinition> loadedModules;
        std::unordered_map<std::string, std::unordered_map<std::string, Parser::Value>> persistentStorage;

        std::vector<CallFrame> callStack;
    };

}