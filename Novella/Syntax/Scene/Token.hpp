#pragma once
#include <string>
namespace Novella::Syntax::Scene{

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

            LParen,
            RParen,

            Comma,
        
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