#pragma once
#include <functional>
#include <cstdint>
#include <unordered_map>

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
        
        using FactoryFunc = std::function<void(NScript::Runtime::Context&, const NScene::Parser::ObjectDefinition&)>;

        void registerType(uint32_t type, FactoryFunc creator);

        void build(uint32_t type, NScript::Runtime::Context& context, const NScene::Parser::ObjectDefinition& definition) const;

        private:

        std::unordered_map<uint32_t, FactoryFunc> creators;
        
        void registerDefaultComponents();

    };

}