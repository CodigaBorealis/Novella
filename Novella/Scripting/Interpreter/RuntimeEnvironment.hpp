#pragma once
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include "../Parser/Expression.hpp"
#include "StatementEvaluator.hpp"
#include "../Parser/Definition.hpp"
#include "NativeFunction.hpp"
#include "RuntimeContext.hpp"
#include <utility>

namespace Novella::NScript::Parser{

    struct Script;

}

namespace Novella{

    class Engine;
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

        void initializeContext(Engine& engine);

        void registerCoreFunctions();

        void registerData(const Parser::Script& script);

        Parser::Value& getVariable(const std::string& name);

        void setVariable(const std::string& name, const Parser::Value& value);

        void clear();

        const Parser::FunctionDefinition& getFunction(const std::string& name);

        void registerFunction(const Parser::FunctionDefinition& definition);

        //Maybe i should just work at a convenience store instead because what even is this anymore
        template <typename Return, typename... Args>

        void registerNativeFunction(const std::string& name, Return(*function)(Context&, Args...)){

            nativeFunctions.emplace(name, [this, function, name](Context& context, const std::vector<Parser::Value>& values) -> Parser::Value{

                if(values.size() != sizeof...(Args)) throw std::runtime_error("Argument mismatch for native function: " + name);

                auto unpacker = [this, function, &context, &values]<std::size_t...Is>(std::index_sequence<Is...>){

                    if constexpr(std::is_void_v<Return>){

                        function(context, values[Is].template get<Args>()...);

                        return Parser::Value{};

                    }else{

                        return Parser::Value{function(context, values[Is].template get<Args>()...)};
                    }
                };

                return unpacker(std::make_index_sequence<sizeof...(Args)>{});
            });
        }

        void printNativeFunctionAddresses() const;

        void createVariable(const std::string& name, const Parser::Value& value);
        
        Parser::Value callNativeFunction(const std::string& name, const std::vector<Parser::Value>& args);

        bool isNativeFunction(const std::string& name) const;

        bool isScriptFunction(const std::string& name) const;

        size_t loadedFunctions() const;

        private:
        
        std::unordered_map<std::string, Parser::Value> variables;
        std::unordered_map<std::string, Parser::FunctionDefinition> scriptFunctions;
        std::unordered_map<std::string, NativeFunction> nativeFunctions;

        std::unordered_map<std::string, std::unordered_map<std::string, Parser::Value>> persistentStorage;

        std::vector<CallFrame> callStack;

        Context runtimeContext;
    };

}