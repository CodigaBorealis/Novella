#pragma once
#include "../../Scripting/Parser/Script.hpp"
#include "../../Scripting/Parser/Definition.hpp"

namespace Novella::Traits{

    struct Scriptable{

        virtual ~Scriptable() = default;
        
        void setScript(NScript::Parser::Script& scriptAST){
            
            script = scriptAST;
        }

        const NScript::Parser::Script& getScript() const{
            
            return script;
        }

        protected:

        NScript::Parser::Script script;
    };

}