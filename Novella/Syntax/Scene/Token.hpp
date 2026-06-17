#pragma once
#include <string>
namespace Novella::Syntax::Scene{

    struct Token{

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

        Type type;

        std::string text;
    };

}