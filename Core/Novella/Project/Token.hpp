#pragma once
#include <string>

namespace Novella::Project{

    struct Token{

        Token() = delete;

        enum class Type : int{

            Identifier,

            String,
            Number,
            Boolean,
            
            Equals,
            
            LBrace,
            RBrace,
            
            EndOfFile
        };

        Token(Type type, const std::string& text)
            :
            type(type),
            text(text)
            {}
        Type type;

        std::string text;
    };
}