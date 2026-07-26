#pragma once
#include "../Traits/Object.hpp"
#include "../Traits/Composite.hpp"
#include <memory>
#include "../../Scripting/Interpreter/RuntimeContext.hpp"
#include "../../Scene/Parser/SceneDefinition.hpp"

namespace Novella::Generic{
 
    class UserWidget : public Traits::Composite,public Traits::RegisteredObject<UserWidget>{

        public:
        
        std::unique_ptr<Traits::Object> create(NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition&);

        UserWidget() = default;

    };
}