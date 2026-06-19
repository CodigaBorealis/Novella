#pragma once
#include <variant>
#include "../Expression.hpp"
#include <unordered_map>
#include <optional>

namespace Novella::Input{

    struct KeyEvent;

    struct ClickEvent;
}

namespace Novella::Syntax::NovellaScript{

    class EventHandler{

        public:

        using Event = std::variant<Input::KeyEvent, Input::ClickEvent>;

        std::optional<Expression> getExpressionFromEvent(const Event& event);
        
        void clear();
        
        private:

    struct RuntimeBinding{
            
            std::string triggerName;
            std::shared_ptr<FunctionCallExpression> callbackAction;
        };

        std::unordered_map<std::string, std::vector<RuntimeBinding>> activeBindings;   

    };

}