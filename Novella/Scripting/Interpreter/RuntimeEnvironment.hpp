#pragma once
#include <unordered_map>
#include <vector>
#include "../Parser/Expression.hpp"
#include "StatementEvaluator.hpp"
#include "../Parser/Definition.hpp"
#include "NativeFunction.hpp"

namespace Novella::NScript::Parser{

    struct Script;

}

namespace Novella::NScript::Runtime{

    class StatementEvaluator;

    class RuntimeEnvironment{

        struct CallFrame{

            std::string functionName;
            std::unordered_map<std::string, Parser::Value> locals;
        };

        public:

        RuntimeEnvironment() = default;

        void registerData(const Parser::Script& script);

        Parser::Value& getVariable(const std::string& name);

        void setVariable(const std::string& name, const Parser::Value& value);

        void clear();

        const Parser::FunctionDefinition& getFunction(const std::string& name);

        void registerFunction(const Parser::FunctionDefinition& definition);

        template <typename Class, typename Return, typename... Args>

        void registerNativeFunction(const std::string& name, Class* object, Return(Class::*method)(Args...) const){
            
        }

        template <typename Class, typename Return, typename... Args>

        void registerNativeFunction(const std::string& name, Class* object, Return(Class::*method)(Args...)){

        }

        void createVariable(const std::string& name, const Parser::Value& value);
    
        private:

        void registerNativeFunction(const std::string& name, const NativeFunction& function);
        
        std::unordered_map<std::string, Parser::Value> variables;
        std::unordered_map<std::string, Parser::FunctionDefinition> scriptFunctions;
        std::unordered_map<std::string, NativeFunction> nativeFunctions;

        std::unordered_map<std::string, std::unordered_map<std::string, Parser::Value>> persistentStorage;

        std::vector<CallFrame> callStack;
    };

}