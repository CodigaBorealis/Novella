#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include "../../Components/Traits/Object.hpp"
namespace Novella::NScript::Runtime{

    struct Context;

}

namespace Novella::NScene::Parser{

    struct ObjectDefinition;
}

namespace Novella::NScene::Serialization{

    class ComponentFactory{

        public:

        ComponentFactory();
        
        using FactoryFunc = std::function<std::unique_ptr<Traits::Object>(NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition&)>;

        void registerType(const std::string& type, FactoryFunc creator);

        std::unique_ptr<Traits::Object> build(NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition& definition) const;
        
        std::unique_ptr<Traits::Object> create(NScript::Runtime::Context& context, const Parser::ObjectDefinition& definition);

        private:

        std::unordered_map<std::string, FactoryFunc> creators;
        
        void registerDefaultComponents();

    };

}