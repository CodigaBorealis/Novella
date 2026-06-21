#pragma once
#include "../Parser/Expression.hpp"
#include <unordered_map>
#include <optional>
#include "../..//Systems/Input/InputEvent.hpp"

namespace Novella::NScript::Runtime{

    class EventHandler{

        public:

        std::optional<Parser::Expression> getExpressionFromEvent(const Event& event);
        
        void clear();
        
        private:

    struct RuntimeBinding{
            
            std::string triggerName;
            std::shared_ptr<Parser::FunctionCallExpression> callbackAction;
        };

        std::unordered_map<uint64_t, std::vector<RuntimeBinding>> activeBindings;   

    };

}