#pragma once
#include <string>
namespace Novella::NScript::Parser{

    struct Token{

        Token() = delete;

        enum class Type : int{

            Identifier,
            String,
            Number,
            Boolean,

            If,
            Then,
            EndIf,
            EndFunction,

            Else,
            Var,
            Define,
            Return,
            From,

            Assign,
            Equals,
            NotEquals,

            Less,
            Greater,
            LessEquals,
            GreaterEquals,

            Plus,

            Minus,

            Multiply,

            Divide,

            Modulo,

            Increment,
            Decrement,

            And,
            Or,
            Not,

            LParen,
            RParen,

            LBracket,
            RBracket,

            Comma,
            SemiColon,
            Colon,
            Dot,


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